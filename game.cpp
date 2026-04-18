#include"game.h"
#include <iostream>
#include<cstdlib>
#include<Windows.h>
#include<conio.h>
Game::Game() :score(0), isGameOver(false), snake(width, height){
	drawBorder();
}
void Game::reset() {
	drawBorder();
    snake=Snake(width, height);
    score = 0;
    speed = 3;
    isGameOver = false;
    generateFood();
}
//状态：展示菜单
Game::GameState Game::menu()
{
	int consoleWidth, consoleHeight;
	getConsoleSize(consoleWidth, consoleHeight);
	system("cls");
	std::cout << "========================================================================" << '\n';
	std::cout << "                          贪吃蛇-控制台版" << '\n';
	std::cout << "========================================================================" << '\n' << '\n';
	std::cout << "【控制】" << '\n';
	std::cout << "  ↑ ↓ ← →   : 移动（方向键)（推荐）" << '\n';
	std::cout << "  W A S D   : 移动（英文输入法）" << '\n';
	std::cout << "  X         : 退出" << '\n';
	std::cout << "  空格      : 暂停/恢复" << '\n';
	std::cout << '\n';
	//规则
	std::cout << "【规则】" << '\n';
	std::cout << " 吃F变长会根据当前蛇的速度等级加上对应的分数，例如吃到F时speed=2时，此时score+2,"
		<<"撞墙#或撞到自身0结束" << '\n' << '\n';
	//提示
	std::cout << "【提示】" << '\n';
	std::cout << " 使用方向键则会有更好的游戏体验" << '\n';
	std::cout << " 游戏过程中不要改变窗口大小，否则可能导致游戏显示错误" << '\n';
	std::cout << " 游戏过程中速度会实时显示" << '\n' ;
	std::cout << " 为了增强趣味性，游戏可以提高加速机制，即长按对应方向的键可以加速，转向或不操作，速度回到默认值"  <<'\n';
	std::cout << " 也可以长按对应相反方向的键减速，转向或不操作，速度回到默认值"  <<'\n';
	std::cout << " 当前控制台窗口大小：" << consoleWidth << " × " << consoleHeight << '\n';
	std::cout << " 在游戏开始之前，你有如下选项：" << '\n';
	std::cout << "1.直接开始游戏" << '\n';
	std::cout << "2.调整窗口设置" << '\n';
	std::cout << "3.调整速度" << '\n';
	std::cout << "其他任意键退出" << '\n';
	if (width >= consoleWidth - 3 || height >= consoleHeight - 3) {
		std::cout << "当前窗口可能显示不全，建议调整窗口后选择2" << '\n';
	}
	std::cout << "请输入：";
	int option;
	std::cin >> option;
	if (option == 1) {
		reset();
		return Game::PLAYING;
	}
	else if (option == 2) {
		std::cout << " 请输入你要的地图宽度(5-" << consoleWidth - 4 << "):";
		std::cin >> width;
		if (width < 5) {
			width = 5;
			std::cout << "输入宽度太小，已经自适应为5" << '\n';
		}
		else if (width > consoleWidth - 3) {
			width = consoleWidth - 4;
			std::cout << "输入宽度太大，已经自适应为" << consoleWidth - 4 << '\n';
		}
		std::cout << " 请输入你要的地图高度(5-" << consoleHeight - 2 << "):";
		std::cin >> height;
		if (height < 5) {
			height = 5;
			std::cout << "输入高度太小，已经自适应为5" << '\n';
		}
		else if (height > consoleHeight - 3) {
			height = consoleHeight - 4;
			std::cout << "输入高度太大，已经自适应为" << consoleWidth - 4 << '\n';
		}
		std::cout << "调整窗口成功" << '\n';
		system("pause");
		return MENU;
	}
	else if (option == 3) {
		std::cout << "请选择你要的默认初始速度（1-7）：";
		std::cin >> defaultSpeed;
		if (defaultSpeed < 1) {
			defaultSpeed = 1;
			std::cout << " 输入速度太小已经自适应为1！！！";
		}
		else if (defaultSpeed > 7) {
			defaultSpeed = 7;
			std::cout << " 输入速度太大已经自适应为7！！！";
		}
		speed = defaultSpeed;
		std::cout << "设置速度成功当前速度为：" << speed<<'\n';
		system("pause");
		return MENU;
	}
	return PLAYING;
}
//状态：游戏进行
Game::GameState Game::playing()
{
	while (state==PLAYING) {
		input();
		logic();
		if (speed < 1)speed = 1;
		if (speed > 7)speed = 7;
		draw();
		Sleep(delays[speed - 1]);
	}
	return state;
}
Game::GameState Game::pause()
{
	gotoxy(0, height + 3); std::cout << "游戏已暂停，请按空格恢复";
	while (true) {
		int c = _getch();
		if (c == 32) {
			return Game::PLAYING;
		}
		else if (tolower(c) == 'x') {
			return Game::MENU;
		}
	}
	return Game::PAUSE;
}
Game::GameState Game::End()
{	
	system("cls");
	gotoxy(0, height / 2);
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
			reset();//重置游戏状态
			return Game::PLAYING;
		}
		else if (ch == '2') {
			return Game::MENU;
		}
		else {
			return Game::EXIT;
		}
	}
	return EXIT;
}
void Game::logic()
{
    if (!snake.logic(width, height, score)) {
		state = GAMEOVER;
        return;
    }
	//尾删除
	if (snake.showHead() == foodPos) {
		score+=speed;
		generateFood();
	}
	else {	
        snake.popTail();
	}
}
void Game::draw()
{
	//绘制头
	gotoxy(snake.showHead().first, snake.showHead().second); std::cout << "0";
	//用空格覆盖蛇尾
	if (snake.prevTail.first != 0 && snake.prevTail.second != 0) {
		gotoxy(snake.prevTail.first, snake.prevTail.second); std::cout << " ";
	}
	gotoxy(width / 2 - 2, height + 2); std::cout << "Score: " << score<<" 当前速度为："<<speed;
	gotoxy(0, height + 3); std::cout << "游戏进行中，可按空格暂停";
	//绘制食物
	gotoxy(foodPos.first, foodPos.second); std::cout << 'F';
}
void Game::input()
{
	Snake::Direction dir= snake.getDir();
	Snake::Direction oldDir = dir;
	//判断方向的同时可以通过长按顺逆方向加块和减慢速度
	if (_kbhit()) {
		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72:dir = Snake::UP; break;
			case 75: dir = Snake::LEFT;break;
			case 80:dir = Snake::DOWN;break;
			case 77: dir = Snake::RIGHT;break;
			}
		}else {
			char lowerKey = tolower(key);
			switch (lowerKey) {
			case 'w': dir = Snake::UP; break;
			case 'a': dir = Snake::LEFT; break;
			case 's': dir = Snake::DOWN; break;
			case 'd': dir = Snake::RIGHT;break;
			case 'x': state=MENU; break;
			case 32:state=PAUSE; break;
			}
		}
		//方向不变则加速
		if (dir == oldDir) {
			speed++;
		}
		else if (abs(dir - oldDir) == 2) {
			dir = oldDir;
			speed--;
		}
		snake.setDir(dir);
	}
	else {
		speed = defaultSpeed;
	}
}
void Game::getConsoleSize(int& consoleWidth, int& consoleHeight)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void Game::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Game::generateFood()
{
    //随机采样+保底遍历
    //空间被蛇占满
    if (snake.getLength() >= width * height) {
        isGameOver = true;
        return;
    }
    //先随机取200次，成功则退出
    for (int attempt = 0; attempt < 200; attempt++) {
        int fx = rand() % width+1;
        int fy = rand() % height+1;
        if (!snake.isOccupying(fx, fy)) {
            foodPos = { fx,fy };
            return;
        }
    }
    //200次全部失败，保底生成
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (!snake.isOccupying(x, y)) {
                foodPos = { x,y };
                return;
            }
        }
    }
    isGameOver = true;
}
void Game::drawBorder()
{
	system("cls");
	for (int i = 0; i <= width+1; ++i) {
		gotoxy(i, 0); std::cout << '#';
		gotoxy(i, height+1); std::cout << '#';
	}
	for (int j = 1; j <= height; ++j) {
		gotoxy(0, j); std::cout << '#';
		gotoxy(width+1,j); std::cout << '#';
	}
}
