#include "game.h"
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>

// 闈欐€佹暟缁勫畾涔?const int Game::delays[7] = {250, 175, 122, 85, 60, 42, 20};

// ============================================
// 鏋勯€犲嚱鏁伴噸杞藉疄鐜?// ============================================

Game::Game() : score(0), isGameOver(false), 
               snake(std::make_shared<Snake>(width, height)),
               food(std::make_shared<Food>(0, 0)) {
    drawBorder();
    generateFood();
    
    // 娣诲姞娓告垙瀵硅薄鍒扮鐞嗗垪琛紝婕旂ず鍔ㄦ€佸叧鑱?    addGameObject(snake);
    addGameObject(food);
}

Game::Game(int w, int h) : width(w), height(h), score(0), isGameOver(false), 
                           snake(std::make_shared<Snake>(w, h)),
                           food(std::make_shared<Food>(0, 0)) {
    drawBorder();
    generateFood();
    
    addGameObject(snake);
    addGameObject(food);
}

Game::Game(int w, int h, int initialSpeed) : width(w), height(h), score(0), 
                                               isGameOver(false), 
                                               snake(std::make_shared<Snake>(w, h)),
                                               food(std::make_shared<Food>(0, 0)),
                                               defaultSpeed(initialSpeed), 
                                               speed(initialSpeed) {
    drawBorder();
    generateFood();
    
    addGameObject(snake);
    addGameObject(food);
}

// ============================================
// 铏氭瀽鏋勫嚱鏁板疄鐜?// ============================================
Game::~Game() {
    gameObjects.clear();
}

void Game::addGameObject(std::shared_ptr<GameObject> obj) {
    gameObjects.push_back(obj);
}

// ============================================
// 鍔ㄦ€佸叧鑱旀紨绀猴細閫氳繃鍩虹被鎸囬拡璋冪敤铏氬嚱鏁?// 杩愯鏃舵牴鎹疄闄呭璞＄被鍨嬭皟鐢ㄥ搴旂殑render瀹炵幇
// ============================================
void Game::renderAllObjects() const {
    for (const auto& obj : gameObjects) {
        // 鍔ㄦ€佸叧鑱旓細缂栬瘧鏃朵笉鐭ラ亾鍏蜂綋绫诲瀷锛岃繍琛屾椂纭畾
        obj->render();
    }
}

void Game::reset() {
    drawBorder();
    snake = std::make_shared<Snake>(width, height);
    score = 0;
    speed = defaultSpeed;
    isGameOver = false;
    generateFood();
    
    // 閲嶇疆娓告垙瀵硅薄鍒楄〃
    gameObjects.clear();
    addGameObject(snake);
    addGameObject(food);
}

Game::GameState Game::menu() {
    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);
    system("cls");
    std::cout << "========================================================================" << '\n';
    std::cout << "                          璐悆铔?鎺у埗鍙扮増" << '\n';
    std::cout << "========================================================================" << '\n' << '\n';
    std::cout << "銆愭帶鍒躲€? << '\n';
    std::cout << "  鈫?鈫?鈫?鈫?  : 绉诲姩锛堟柟鍚戦敭)锛堟帹鑽愶級" << '\n';
    std::cout << "  W A S D   : 绉诲姩锛堣嫳鏂囪緭鍏ユ硶锛? << '\n';
    std::cout << "  X         : 閫€鍑? << '\n';
    std::cout << "  绌烘牸      : 鏆傚仠/鎭㈠" << '\n';
    std::cout << '\n';
    std::cout << "銆愯鍒欍€? << '\n';
    std::cout << " 鍚僃鍙橀暱浼氭牴鎹綋鍓嶈泧鐨勯€熷害绛夌骇鍔犱笂瀵瑰簲鐨勫垎鏁帮紝渚嬪鍚冨埌F鏃秙peed=2鏃讹紝姝ゆ椂score+2,"
        << "鎾炲#鎴栨挒鍒拌嚜韬?缁撴潫" << '\n' << '\n';
    std::cout << "銆愭彁绀恒€? << '\n';
    std::cout << " 浣跨敤鏂瑰悜閿垯浼氭湁鏇村ソ鐨勬父鎴忎綋楠? << '\n';
    std::cout << " 娓告垙杩囩▼涓笉瑕佹敼鍙樼獥鍙ｅぇ灏忥紝鍚﹀垯鍙兘瀵艰嚧娓告垙鏄剧ず閿欒" << '\n';
    std::cout << " 娓告垙杩囩▼涓€熷害浼氬疄鏃舵樉绀? << '\n';
    std::cout << " 涓轰簡澧炲己瓒ｅ懗鎬э紝娓告垙鍙互鎻愰珮鍔犻€熸満鍒讹紝鍗抽暱鎸夊搴旀柟鍚戠殑閿彲浠ュ姞閫燂紝杞悜鎴栦笉鎿嶄綔锛岄€熷害鍥炲埌榛樿鍊? << '\n';
    std::cout << " 涔熷彲浠ラ暱鎸夊搴旂浉鍙嶆柟鍚戠殑閿噺閫燂紝杞悜鎴栦笉鎿嶄綔锛岄€熷害鍥炲埌榛樿鍊? << '\n';
    std::cout << " 褰撳墠鎺у埗鍙扮獥鍙ｅぇ灏忥細" << consoleWidth << " 脳 " << consoleHeight << '\n';
    std::cout << " 鍦ㄦ父鎴忓紑濮嬩箣鍓嶏紝浣犳湁濡備笅閫夐」锛? << '\n';
    std::cout << "1.鐩存帴寮€濮嬫父鎴? << '\n';
    std::cout << "2.璋冩暣绐楀彛璁剧疆" << '\n';
    std::cout << "3.璋冩暣閫熷害" << '\n';
    std::cout << "鍏朵粬浠绘剰閿€€鍑? << '\n';
    if (width >= consoleWidth - 3 || height >= consoleHeight - 3) {
        std::cout << "褰撳墠绐楀彛鍙兘鏄剧ず涓嶅叏锛屽缓璁皟鏁寸獥鍙ｅ悗閫夋嫨2" << '\n';
    }
    std::cout << "璇疯緭鍏ワ細";
    int option;
    std::cin >> option;
    if (option == 1) {
        reset();
        return PLAYING;
    }
    else if (option == 2) {
        std::cout << " 璇疯緭鍏ヤ綘瑕佺殑鍦板浘瀹藉害(5-" << consoleWidth - 4 << "):";
        std::cin >> width;
        if (width < 5) {
            width = 5;
            std::cout << "杈撳叆瀹藉害澶皬锛屽凡缁忚嚜閫傚簲涓?" << '\n';
        }
        else if (width > consoleWidth - 3) {
            width = consoleWidth - 4;
            std::cout << "杈撳叆瀹藉害澶ぇ锛屽凡缁忚嚜閫傚簲涓? << consoleWidth - 4 << '\n';
        }
        std::cout << " 璇疯緭鍏ヤ綘瑕佺殑鍦板浘楂樺害(5-" << consoleHeight - 2 << "):";
        std::cin >> height;
        if (height < 5) {
            height = 5;
            std::cout << "杈撳叆楂樺害澶皬锛屽凡缁忚嚜閫傚簲涓?" << '\n';
        }
        else if (height > consoleHeight - 3) {
            height = consoleHeight - 4;
            std::cout << "杈撳叆楂樺害澶ぇ锛屽凡缁忚嚜閫傚簲涓? << consoleWidth - 4 << '\n';
        }
        std::cout << "璋冩暣绐楀彛鎴愬姛" << '\n';
        system("pause");
        return MENU;
    }
    else if (option == 3) {
        std::cout << "璇烽€夋嫨浣犺鐨勯粯璁ゅ垵濮嬮€熷害锛?-7锛夛細";
        std::cin >> defaultSpeed;
        if (defaultSpeed < 1) {
            defaultSpeed = 1;
            std::cout << " 杈撳叆閫熷害澶皬宸茬粡鑷€傚簲涓?锛侊紒锛?;
        }
        else if (defaultSpeed > 7) {
            defaultSpeed = 7;
            std::cout << " 杈撳叆閫熷害澶ぇ宸茬粡鑷€傚簲涓?锛侊紒锛?;
        }
        speed = defaultSpeed;
        std::cout << "璁剧疆閫熷害鎴愬姛褰撳墠閫熷害涓猴細" << speed << '\n';
        system("pause");
        return MENU;
    }
    return PLAYING;
}

Game::GameState Game::playing() {
    while (state == PLAYING) {
        input();
        logic();
        if (speed < 1) speed = 1;
        if (speed > 7) speed = 7;
        draw();
        Sleep(delays[speed - 1]);
    }
    return state;
}

Game::GameState Game::pause() {
    gotoxy(0, height + 3); std::cout << "娓告垙宸叉殏鍋滐紝璇锋寜绌烘牸鎭㈠";
    while (true) {
        int c = _getch();
        if (c == 32) {
            return PLAYING;
        }
        else if (tolower(c) == 'x') {
            return MENU;
        }
    }
    return PAUSE;
}

Game::GameState Game::End() {
    system("cls");
    gotoxy(0, height / 2);
    std::cout << "GAME OVER! Final Score: " << score;
    std::cout << '\n';
    system("pause");
    std::cout << "璇烽€夋嫨锛? << '\n';
    std::cout << "1.閲嶆柊寮€濮? << '\n';
    std::cout << "2.杩斿洖鑿滃崟" << '\n';
    std::cout << "鍏朵粬浠绘剰閿€€鍑? << '\n';
    while (true) {
        int ch = tolower(_getch());
        if (ch == '1') {
            reset();
            return PLAYING;
        }
        else if (ch == '2') {
            return MENU;
        }
        else {
            return EXIT;
        }
    }
    return EXIT;
}

void Game::logic() {
    if (!snake->logic(width, height, score)) {
        state = GAMEOVER;
        return;
    }
    if (snake->showHead() == food->getPosition()) {
        score += speed;
        generateFood();
    }
    else {
        snake->popTail();
    }
}

void Game::draw() {
    // 缁樺埗铔囧ご
    gotoxy(snake->showHead().first, snake->showHead().second); 
    std::cout << snake->getRenderChar();
    
    // 鐢ㄧ┖鏍艰鐩栬泧灏?    std::pair<int, int> prevTail = snake->getPrevTail();
    if (prevTail.first != 0 && prevTail.second != 0) {
        gotoxy(prevTail.first, prevTail.second); std::cout << " ";
    }
    
    // 缁樺埗鍒嗘暟鍜岄€熷害
    gotoxy(width / 2 - 2, height + 2); 
    std::cout << "Score: " << score << " 褰撳墠閫熷害涓猴細" << speed;
    gotoxy(0, height + 3); 
    std::cout << "娓告垙杩涜涓紝鍙寜绌烘牸鏆傚仠";
    
    // 缁樺埗椋熺墿
    gotoxy(food->getPosition().first, food->getPosition().second); 
    std::cout << food->getRenderChar();
    
    // 婕旂ず鍔ㄦ€佸叧鑱旓細娓叉煋鎵€鏈夊璞?    renderAllObjects();
}

void Game::input() {
    Snake::Direction dir = snake->getDir();
    Snake::Direction oldDir = dir;
    if (_kbhit()) {
        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: dir = Snake::UP; break;
                case 75: dir = Snake::LEFT; break;
                case 80: dir = Snake::DOWN; break;
                case 77: dir = Snake::RIGHT; break;
            }
        }
        else {
            char lowerKey = tolower(key);
            switch (lowerKey) {
                case 'w': dir = Snake::UP; break;
                case 'a': dir = Snake::LEFT; break;
                case 's': dir = Snake::DOWN; break;
                case 'd': dir = Snake::RIGHT; break;
                case 'x': state = MENU; break;
                case 32: state = PAUSE; break;
            }
        }
        if (dir == oldDir) {
            speed++;
        }
        else if (abs(dir - oldDir) == 2) {
            dir = oldDir;
            speed--;
        }
        snake->setDir(dir);
    }
    else {
        speed = defaultSpeed;
    }
}

void Game::getConsoleSize(int& consoleWidth, int& consoleHeight) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Game::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Game::generateFood() {
    if (snake->getLength() >= width * height) {
        isGameOver = true;
        return;
    }
    for (int attempt = 0; attempt < 200; attempt++) {
        int fx = rand() % width + 1;
        int fy = rand() % height + 1;
        if (!snake->isOccupying(fx, fy)) {
            food->setPosition(fx, fy);
            return;
        }
    }
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (!snake->isOccupying(x, y)) {
                food->setPosition(x, y);
                return;
            }
        }
    }
    isGameOver = true;
}

void Game::drawBorder() {
    system("cls");
    for (int i = 0; i <= width + 1; ++i) {
        gotoxy(i, 0); std::cout << '#';
        gotoxy(i, height + 1); std::cout << '#';
    }
    for (int j = 1; j <= height; ++j) {
        gotoxy(0, j); std::cout << '#';
        gotoxy(width + 1, j); std::cout << '#';
    }
}
