#include<iostream>
#include<deque>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<ctime>
int width = 50, height = 30;
int foodX, foodY;
int score = 0;
bool gameOver = false;
enum Direction{STOP=0,UP,DOWN,LEFT,RIGHT};
Direction dir;
std::deque<std::pair<int, int>>snake;
//上一个可删除蛇尾位置
std::pair<int, int> deleteAbletail;
//隐藏光标
void hiderCursor() {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 100;
	cursor.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
//移动光标
void gotoxy(int x,int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

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
	gotoxy(width + 5, 5); std::cout << "Score: " << score;
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
	snake.clear();//清理上一轮蛇长度残余数据
	snake.push_back({ width / 2, height / 2 });
	snake.push_back({ width / 2 - 1, height / 2 });
	snake.push_back({ width / 2 - 2, height / 2 });//初始化为中间位置，占3格
	dir = RIGHT;
	deleteAbletail={0,0};
	score = 0;
	gameOver = false;
	generateFood();
	hiderCursor();
	system("cls");
}
//处理输入
void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w': if (dir != DOWN)dir = UP; break;
		case 'a': if (dir != RIGHT)dir = LEFT; break;
		case 's': if (dir != UP)dir = DOWN; break;
		case 'd': if (dir != LEFT)dir= RIGHT; break;
		case 'x': gameOver=true;break;
		}
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
int main() {
	srand(time(0));
	setup();
	while (!gameOver) {
		draw();
		input();
		logic();
		Sleep(100);
	}
	gotoxy(width / 2, height / 2 + 2);
	std::cout << "GAME OVER! Final Score: " << score;

	gotoxy(0, height + 5);
	return 0;
}
