#pragma once
#include "gameobject.h"
#include <deque>

// ============================================
// 知识点：虚基类 (Virtual Base Class)
// --------------------------------------------
// Snake类同时继承GameObject和IRenderable两个虚基类。
// 如果将来有其他类也继承这两个基类，并且某个类同时继承Snake和Food，
// 使用virtual继承可以确保GameObject和IRenderable在最终派生类中只存在一份。
// ============================================

class Snake : virtual public GameObject, virtual public IRenderable {
public:
    // 将枚举移到 public 以便 Game 类使用
    enum Direction { UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4 };
    
private:
    std::deque<std::pair<int, int>> body;
    char renderChar = 'O';
    
    Direction dir = RIGHT;
    
    std::pair<int, int> prevTail;
    
public:
    // ============================================
    // 知识点：构造函数重载 (Constructor Overloading)
    // --------------------------------------------
    // 提供多种初始化方式：
    // 1. 默认构造函数：创建默认长度的蛇
    // 2. 带地图参数的构造函数：在地图中心创建蛇
    // 3. 带长度参数的构造函数：自定义初始长度
    // 4. 带自定义渲染字符的构造函数：使用自定义字符显示蛇
    // ============================================
    
    // 默认构造函数
    Snake();
    
    // 带地图宽高的构造函数
    Snake(int width, int height);
    
    // 带地图宽高和初始长度的构造函数
    Snake(int width, int height, int initialLength);
    
    // 带地图宽高、初始长度和自定义渲染字符的构造函数
    Snake(int width, int height, int initialLength, char customChar);
    
    // ============================================
    // 知识点：虚析构函数 (Virtual Destructor)
    // --------------------------------------------
    // 当类用作基类时，析构函数应该声明为virtual。
    // 这样通过基类指针删除派生类对象时，会先调用派生类析构函数，
    // 再调用基类析构函数，确保资源正确释放。
    // ============================================
    virtual ~Snake();
    
    // 虚函数实现 - 动态关联
    void render() const override;
    std::pair<int, int> getPosition() const override;
    bool isAtPosition(int x, int y) const override;
    char getRenderChar() const override;
    
    void pushHead(std::pair<int, int> newHead);
    void popTail();
    int getLength() const;
    bool isOccupying(int x, int y) const;
    std::pair<int, int> showHead() const;
    std::pair<int, int> getTail() const;
    Direction getDir() const;
    void setDir(Direction dir);
    bool logic(int width, int height, int& score);
    
    // 获取上一次删除的尾巴位置
    std::pair<int, int> getPrevTail() const;
    
    // ============================================
    // 知识点：友元函数 (Friend Function)
    // --------------------------------------------
    // 友元函数不是类的成员函数，但可以访问类的私有和保护成员。
    // 这里声明Game类为友元，允许Game类直接访问Snake的私有状态。
    // 友元关系是单向的，不继承，不传递。
    // ============================================
    friend class Game;
    
    // 友元函数：重载输出运算符
    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);
};
