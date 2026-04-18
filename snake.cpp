#include"snake.h"

Snake::Snake(int width,int height)
{
	body.push_back({ width / 2, height / 2 });
	body.push_back({ width / 2 - 1, height / 2 });
	body.push_back({ width / 2 - 2, height / 2 });//初始化为中间位置，占3格
}

void Snake::pushHead(std::pair<int,int> newHead)
{
	body.push_front(newHead);
}

void Snake::popTail()
{
	prevTail = body.back();
	body.pop_back();
}

int Snake::getLength()
{
	return body.size();
}

bool Snake::isOccupying(int x, int y)
{
	for (auto& segment : body) {
		if (x == segment.first && y == segment.second) {
			return true;
		}
	}
	return false;
}

std::pair<int, int> Snake::showHead()
{
	return body.front();
}

std::pair<int, int> Snake::getTail()
{
	return body.back();
}

Snake::Direction Snake::getDir()
{
	return dir;
}

void Snake::setDir(Direction dir)
{
	this->dir = dir;
}

bool Snake::logic(int width, int height, int& score)
{
	//计算新头
	std::pair<int, int> newHead = body.front();
	switch (dir) {
	case UP:     newHead.second--; break;
	case DOWN:     newHead.second++; break;
	case LEFT:     newHead.first--; break;
	case RIGHT:     newHead.first++; break;
	default:break;
	}
	//检查碰撞或者撞自己
	if (newHead.first <= 0 || newHead.first > width || newHead.second <= 0 || newHead.second > height) {
		return false;
	}
	for (auto& segment : body) {
		if (segment == newHead) {
			return false;
		}
	}
	body.push_front(newHead);
	
}
