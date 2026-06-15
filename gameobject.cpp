#include "gameobject.h"
#include <iostream>

// ============================================
// 知识点：构造函数重载 (Constructor Overloading)
// --------------------------------------------
// 构造函数重载允许类定义多个同名构造函数，但参数列表不同。
// 这提供了多种对象创建方式，适应不同场景的需求。
// 
// 重载规则：
// 1. 参数数量不同
// 2. 参数类型不同
// 3. 参数顺序不同
// ============================================

// 默认构造函数
Food::Food() : position({0, 0}), renderChar('F') {}

// 带坐标参数的构造函数
Food::Food(int x, int y) : position({x, y}), renderChar('F') {}

// 带坐标和自定义字符的构造函数
Food::Food(int x, int y, char customChar) : position({x, y}), renderChar(customChar) {}

void Food::render() const {
    // 实际渲染由Game类控制，这里提供接口
}

std::pair<int, int> Food::getPosition() const {
    return position;
}

bool Food::isAtPosition(int x, int y) const {
    return position.first == x && position.second == y;
}

char Food::getRenderChar() const {
    return renderChar;
}

void Food::setPosition(int x, int y) {
    position = {x, y};
}

// 友元函数实现 - 可以直接访问Food的私有成员position和renderChar
std::ostream& operator<<(std::ostream& os, const Food& food) {
    os << "Food at (" << food.position.first << ", " << food.position.second << ")";
    return os;
}
