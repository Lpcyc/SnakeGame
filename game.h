#pragma once
#include "gameobject.h"
#include "snake.h"
#include <utility>
#include <vector>
#include <memory>

// ============================================
// 知识点：动态关联 (Dynamic Binding / Polymorphism)
// --------------------------------------------
// Game类使用GameObject指针/引用来管理游戏对象。
// 通过虚函数实现运行时多态，调用正确的对象实现。
// ============================================

class Game {
private:
    int width = 50;
    int height = 25;
    int score = 0;
    bool isGameOver = false;
    int defaultSpeed = 3;
    int speed = 3;
    
    // 使用shared_ptr管理游戏对象，演示动态关联
    std::shared_ptr<Snake> snake;
    std::shared_ptr<Food> food;
    
    // 使用基类指针存储游戏对象，用于演示动态关联
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    
public:
    enum GameState { MENU, PLAYING, GAMEOVER, PAUSE, EXIT };
    GameState state = MENU;
    static const int delays[7];
    int SPEED_LEVEL_MIN = 1;
    static constexpr int SPEED_LEVEL_MAX = 7;
    
    // ============================================
    // 知识点：构造函数重载 (Constructor Overloading)
    // --------------------------------------------
    // 提供多种初始化方式：
    // 1. 默认构造函数：使用默认地图大小
    // 2. 带地图参数的构造函数：自定义地图大小
    // 3. 带地图和速度的构造函数：自定义地图大小和初始速度
    // ============================================
    Game();
    Game(int w, int h);
    Game(int w, int h, int initialSpeed);
    
    // ============================================
    // 知识点：虚析构函数 (Virtual Destructor)
    // --------------------------------------------
    // 虽然Game不是基类，但作为一个管理动态对象的类，
    // 使用虚析构函数是良好的设计习惯，确保派生类正确释放资源。
    // ============================================
    virtual ~Game();
    
    void generateFood();
    void reset();
    GameState menu();
    GameState playing();
    GameState pause();
    GameState End();
    
    // 添加游戏对象到管理列表
    void addGameObject(std::shared_ptr<GameObject> obj);
    
    // 渲染所有游戏对象 - 演示动态关联
    void renderAllObjects() const;
    
private:
    void logic();
    void draw();
    void input();
    void getConsoleSize(int&, int&);
    void drawBorder();
    void gotoxy(int, int);
};
