#pragma once
#include<deque>
class Snake
{
	std::deque<std::pair<int, int>> body;//使用双端队列存储蛇的身体节点
public:
	std::pair<int, int> prevTail;//上次残留尾端，{0，0}代表没有残留
	enum Direction { UP=1, RIGHT =2, DOWN=3, LEFT=4 };
	
	Snake(int,int);
	void pushHead(std::pair<int,int>);
	void popTail();
	int getLength();
	bool isOccupying(int, int);
	std::pair<int, int>showHead();
private:
	Direction dir=RIGHT;
public:
	std::pair<int, int> getTail();
	Direction getDir();
	void setDir(Direction dir);
	bool logic(int, int, int&);

};

