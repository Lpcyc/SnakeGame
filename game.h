#pragma once
#include"snake.h"
#include<utility>

class Game {
private:
	int width = 50;
	int height=25;
	int score = 0;
	std::pair<int, int> foodPos;
	bool isGameOver = false;
	Snake snake;
	int defaultSpeed = 3;
	int speed=3;
public:
	enum GameState { MENU, PLAYING, GAMEOVER, PAUSE, EXIT };
	GameState state = MENU;
	static constexpr int delays[] = {250,175,122,85,60,42,20};
	int SPEED_LEVEL_MIN = 1;
	static constexpr int SPEED_LEVEL_MAX = 7;
	Game();
	void generateFood();
	void reset();
	GameState menu();
	GameState playing();
	GameState pause();
	GameState End();
private:
	void logic();
	void draw();
	void input();
	//获取当前控制台窗口大小
	void getConsoleSize(int&, int&);
	//绘制边框
	void drawBorder();
	void gotoxy(int, int);

};