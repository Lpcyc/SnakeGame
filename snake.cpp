#include "snake.h"
#include <iostream>

// ============================================
// 鏋勯€犲嚱鏁伴噸杞藉疄鐜?// ============================================

// 榛樿鏋勯€犲嚱鏁?Snake::Snake() {
    body.push_back({10, 10});
    body.push_back({9, 10});
    body.push_back({8, 10});
    prevTail = {0, 0};
}

// 甯﹀湴鍥惧楂樼殑鏋勯€犲嚱鏁?Snake::Snake(int width, int height) {
    int centerX = width / 2;
    int centerY = height / 2;
    body.push_back({centerX, centerY});
    body.push_back({centerX - 1, centerY});
    body.push_back({centerX - 2, centerY});
    prevTail = {0, 0};
}

// 甯﹀湴鍥惧楂樺拰鍒濆闀垮害鐨勬瀯閫犲嚱鏁?Snake::Snake(int width, int height, int initialLength) {
    int centerX = width / 2;
    int centerY = height / 2;
    if (initialLength < 2) initialLength = 2;
    for (int i = 0; i < initialLength; ++i) {
        body.push_back({centerX - i, centerY});
    }
    prevTail = {0, 0};
}

// 甯﹀湴鍥惧楂樸€佸垵濮嬮暱搴﹀拰鑷畾涔夋覆鏌撳瓧绗︾殑鏋勯€犲嚱鏁?Snake::Snake(int width, int height, int initialLength, char customChar) {
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
// 铏氭瀽鏋勫嚱鏁板疄鐜?// ============================================
Snake::~Snake() {
    body.clear();
}

void Snake::render() const {
    // 娓叉煋閫昏緫鐢盙ame绫诲鐞?}

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

// 鍙嬪厓鍑芥暟瀹炵幇
std::ostream& operator<<(std::ostream& os, const Snake& snake) {
    os << "Snake length: " << snake.getLength() << ", Head at (" 
       << snake.showHead().first << ", " << snake.showHead().second << ")";
    return os;
}
