#include "snake.h"
#include <iostream>

// ============================================
// 构造函数重载实现
// ============================================

// 默认构造函数
Snake::Snake() {
    body.push_back({10, 10});
    body.push_back({9, 10});
    body.push_back({8, 10});
    prevTail = {0, 0};
}

// 带地图宽高的构造函数
Snake::Snake(int width, int height) {
    int centerX = width / 2;
    int centerY = height / 2;
    body.push_back({centerX, centerY});
    body.push_back({centerX - 1, centerY});
    body.push_back({centerX - 2, centerY});
    prevTail = {0, 0};
}

// 带地图宽高和初始长度的构造函数
Snake::Snake(int width, int height, int initialLength) {
    int centerX = width / 2;
    int centerY = height / 2;
    if (initialLength < 2) initialLength = 2;
    for (int i = 0; i < initialLength; ++i) {
        body.push_back({centerX - i, centerY});
    }
    prevTail = {0, 0};
}

// 带地图宽高、初始长度和自定义渲染字符的构造函数
Snake::Snake(int width, int height, int initialLength, char customChar) {
    int centerX = width / 2;
    int centerY = height / 2;
    if (initialLength < 2) initialLength = 2;
    for (int i = 0; i < initialLength; ++i) {
        body.push_back({centerX - i, centerY});
    }
    prevTail = {0, 0};
    renderChar = customChar;
}

// ============================================
// 虚析构函数实现
// ============================================
Snake::~Snake() {
    body.clear();
}

void Snake::render() const {
    // 渲染逻辑由Game类处理
}

std::pair<int, int> Snake::getPosition() const {
    return showHead();
}

bool Snake::isAtPosition(int x, int y) const {
    return isOccupying(x, y);
}

char Snake::getRenderChar() const {
    return renderChar;
}

void Snake::pushHead(std::pair<int, int> newHead) {
    body.push_front(newHead);
}

void Snake::popTail() {
    prevTail = body.back();
    body.pop_back();
}

int Snake::getLength() const {
    return body.size();
}

bool Snake::isOccupying(int x, int y) const {
    for (const auto& segment : body) {
        if (x == segment.first && y == segment.second) {
            return true;
        }
    }
    return false;
}

std::pair<int, int> Snake::showHead() const {
    return body.front();
}

std::pair<int, int> Snake::getTail() const {
    return body.back();
}

Snake::Direction Snake::getDir() const {
    return dir;
}

void Snake::setDir(Direction d) {
    dir = d;
}

std::pair<int, int> Snake::getPrevTail() const {
    return prevTail;
}

bool Snake::logic(int width, int height, int& score) {
    std::pair<int, int> newHead = body.front();
    switch (dir) {
        case UP:    newHead.second--; break;
        case DOWN:  newHead.second++; break;
        case LEFT:  newHead.first--; break;
        case RIGHT: newHead.first++; break;
    }
    if (newHead.first <= 0 || newHead.first > width || newHead.second <= 0 || newHead.second > height) {
        return false;
    }
    for (const auto& segment : body) {
        if (segment == newHead) {
            return false;
        }
    }
    body.push_front(newHead);
    return true;
}

// 友元函数实现
std::ostream& operator<<(std::ostream& os, const Snake& snake) {
    os << "Snake length: " << snake.getLength() << ", Head at (" 
       << snake.showHead().first << ", " << snake.showHead().second << ")";
    return os;
}
