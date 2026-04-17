#include<iostream>
#include<deque>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<ctime>
int width = 50, height = 25;
int foodX, foodY;
int score = 0;
bool gameOver = false;
bool paused = false;//游戏暂停
int frame = 120;
int dspeed = 100;
//游戏状态枚举
enum GameState{MENU, PLAYING, GAMEOVER,PAUSE, EXIT};
//方向枚举
enum Direction{STOP=0,UP,DOWN,LEFT,RIGHT};

Direction dir;
std::deque<std::pair<int, int>>snake;
//上一个可删除蛇尾位置
std::pair<int, int> deleteAbletail;
//是否回到主菜单
bool returnMenu = false;
//是否重新开始
bool restart = false;
//获取当前控制台窗口大小
void getConsoleSize(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
//隐藏光标
void hiderCursor() {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 100;
	cursor.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
//移动光标
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
//生成新食物
void generateFood() {
	std::vector<std::pair<int, int>> freeSpaces;
	for (int i = 1; i <= width; i++) {
		for (int j = 1; j <= height; j++) {
			bool occupied = false;
			for (auto& segment : snake) {
				if (segment.first == i && segment.second == j) {
					occupied = true;
					break;
				}
			}
			if (!occupied) {
				freeSpaces.push_back({ i,j });
			}
		}
	}
	if (freeSpaces.empty()) {
		gameOver = true;
		gotoxy(width / 2, height / 2);
		std::cout << " YOU WIN!";
		return;
	}
	int index = rand() % freeSpaces.size();
	foodX = freeSpaces[index].first;
	foodY = freeSpaces[index].second;
}
//初始化游戏
void setup() {
	srand(time(0));
	snake.clear();//清理上一轮蛇长度残余数据
	snake.push_back({ width / 2, height / 2 });
	snake.push_back({ width / 2 - 1, height / 2 });
	snake.push_back({ width / 2 - 2, height / 2 });//初始化为中间位置，占3格
	dir = RIGHT;
	deleteAbletail = { 0,0 };
	score = 0;
	frame = 120;
	gameOver = false;
	generateFood();
	hiderCursor();
	system("cls");

}
GameState showMenu(int &width,int& height) {
	int consoleWidth, consoleHeight;
	getConsoleSize(consoleWidth, consoleHeight);
	std::cout << "========================================================================" << '\n';
	std::cout << "                          贪吃蛇-控制台版" << '\n';
	std::cout << "========================================================================" << '\n'<<'\n';
	std::cout << "【控制】" << '\n';
	std::cout << "  ↑ ↓ ← →   : 移动（方向键)（推荐）" << '\n';
	std::cout << "  W A S D   : 移动（英文输入法）" << '\n';
	std::cout << "  X         : 退出" << '\n';
	std::cout << "  空格      : 暂停/恢复" << '\n';
	std::cout << '\n';
	//规则
	std::cout << "【规则】" << '\n';
	std::cout << " 吃F变长+1分，撞墙#或撞到自身0结束" << '\n'<<'\n';
	//提示
	std::cout << "【提示】" << '\n';
	std::cout << " 使用方向键则会有更好的游戏体验" << '\n';
	std::cout << " 游戏过程中不要改变窗口大小，否则可能导致游戏显示错误" << '\n'<<'\n';
	//当前环境
	std::cout << "【当前环境】" << '\n';
	std::cout << " 当前控制台窗口大小：" << consoleWidth << " × " << consoleHeight << '\n';
	std::cout << " 在游戏开始之前，你有如下选项：" << '\n';
	std::cout << "1.直接开始游戏" << '\n';
	std::cout << "2.调整窗口设置" << '\n'; 
	std::cout << "其他任意键退出" << '\n'; 
	if (width >= consoleWidth-2 || height >= consoleHeight-2) {
		std::cout << "当前窗口可能显示不全，建议调整窗口后选择2"<<'\n';
	}
	std::cout << "请输入：";
	int option;
	std::cin >> option;
	if (option == 1) {
		gameOver = false;
	}
	else if (option == 2) {
		std::cout << " 请输入你要的地图宽度(5-"<<consoleWidth-2<<"):";
		std::cin >> width;
		if (width < 5) {
			std::cout << "输入宽度太小，已经自适应为5" << '\n';
		}
		else if(width>consoleWidth-2){
			std::cout << "输入宽度太大，已经自适应为" << consoleWidth-2<<'\n';
		}
		std::cout << " 请输入你要的地图高度(5-"<<consoleHeight-2<<"):";
		std::cin >> height;
		if (height < 5) {
			std::cout << "输入高度太小，已经自适应为5" << '\n';
		}
		else if (height > consoleHeight - 2) {
			std::cout << "输入宽度太大，已经自适应为" << consoleWidth - 2 << '\n';
		}
		returnMenu = true;
	}
	else {
		return EXIT;
	}
	setup();
	return PLAYING;
}
//绘制边框，食物，蛇
void draw() {
	for (int i = 0; i <= width + 1; i++) {
		gotoxy(i, 0); std::cout << "#";
		gotoxy(i, height+1); std::cout << "#";
	}
	for (int i = 0; i <= height + 1; i++) {
		gotoxy(0, i); std::cout << "#";
		gotoxy(width+1, i); std::cout << "#";
	}
	//绘制食物
	gotoxy(foodX, foodY); std::cout << "F";
	//绘制蛇
	//用空格覆盖蛇尾
	if (deleteAbletail.first!=0&&deleteAbletail.second!= 0) {
		gotoxy(deleteAbletail.first, deleteAbletail.second); std::cout << " ";
	}
	for (auto& segment : snake) {
		gotoxy(segment.first, segment.second); std::cout << "0";
	}
	gotoxy(width/2-2, height+2); std::cout << "Score: " << score;
	gotoxy(0, height + 3); std::cout<< "游戏进行中，可按空格暂停";
}
//处理输入
void input() {
	Direction oldDir = dir;
	//判断方向的同时可以通过顺逆方向加块和减慢速度

	if (_kbhit()) {
		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: 
				if (dir != DOWN) {
					dir = UP;
				}
				else { 
					frame += dspeed;
				}break;
			case 75: if (dir != RIGHT) {
					dir = LEFT;
				} else {
					frame += dspeed;
				}break;
			case 80: if (dir != UP) {
					dir = DOWN;
				}else {
					frame += dspeed; 
				} break;
			case 77: if (dir != LEFT) {
					dir = RIGHT;
			}
				   else {
				frame += dspeed;
			}break;
			}
		}
		else {
			char lowerKey = tolower(key);
			switch (lowerKey) {
			case 'w': if (dir != DOWN)dir = UP; else frame += dspeed; break;
			case 'a': if (dir != RIGHT)dir = LEFT; else frame += dspeed; break;
			case 's': if (dir != UP)dir = DOWN; else frame += dspeed; break;
			case 'd': if (dir != LEFT)dir = RIGHT; else frame += dspeed; break;
			case 'x': gameOver = true; break;
			case 63:gameOver=true; returnMenu=true; break;
			case 32:paused = true; break;
			}
		}
		//方向不变则加速
		if (dir == oldDir) {
			frame /= 2;
		}
	}
	
	if (returnMenu == true) {
		returnMenu = false;
		showMenu(width,height);
		return;
	}
}
//游戏逻辑
void logic() {
	//计算新头
	std::pair<int,int> newHead=snake.front();
	switch (dir) {
		case UP:     newHead.second--;break; 
		case DOWN:     newHead.second++;break; 
		case LEFT:     newHead.first--;break; 
		case RIGHT:     newHead.first++;break; 
		default:break;
	}
	//检查碰撞或者撞自己
	if (newHead.first <= 0 || newHead.first > width || newHead.second <= 0 || newHead.second > height) {
		gameOver = true;
		return;
	}
	for (auto& segment : snake) {
		if (segment == newHead) {
			gameOver = true;
			return;
		}
	}
	snake.push_front(newHead);
   //尾删除
	if (newHead.first == foodX && newHead.second == foodY) {
		score++;
		generateFood();
	}
	else {
		deleteAbletail.first = snake.back().first;
		deleteAbletail.second = snake.back().second;
		snake.pop_back();
	}
}
//游戏结束让光标指出显示
void showCursor() {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 100;
	cursor.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
//游戏进行
GameState playing() {
	while (!gameOver) {
		if (paused == true) {
			return PAUSE;
		}
		draw();
		input();
		logic();
		if (frame < 0)frame = 0;
		if (frame > 1000)frame = 1000;
		Sleep(frame);
	}
	return GAMEOVER;
}
//游戏暂停
GameState isPause() {
	gotoxy(0, height + 3);std::cout << "游戏已暂停，请按空格恢复";
	while (paused) {
		int c = _getch();
		if (c == 32) {
			paused = false;
		}
		else if (tolower(c)=='x') {
			return MENU;
		}
	}
	return PLAYING;
}
GameState gameEnd() {

	system("cls");
	gotoxy(0, height/2);
	std::cout << "GAME OVER! Final Score: " << score;
	std::cout << '\n';
	system("pause");
	std::cout << "请选择：" << '\n';
	std::cout << "1.重新开始" << '\n';
	std::cout << "2.返回菜单" << '\n';
	std::cout << "其他任意键退出" << '\n';
	while (true) {
		int ch = tolower(_getch());
		if (ch == '1') {
			setup();//重置游戏状态
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
int main() {
	SetConsoleOutputCP(CP_UTF8);
	GameState state = MENU;
	while (state!=EXIT) {
		if (restart) {
			restart = false;
			state = PLAYING;
		}
		if (returnMenu) {
			returnMenu = false;
			state = MENU;
		}
		switch (state) {
		case MENU:
			state = showMenu(width,height);
			break;
		case PLAYING:
			state = playing();
			break;
		case PAUSE:
			state = isPause();
			break;
		case GAMEOVER:
			state = gameEnd();
			break;
		default:break;
		}
	}

	system("pause");
	showCursor;
	return 0;
}
