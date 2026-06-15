# 贪吃蛇（控制台版）

一个 C++ 控制台贪吃蛇游戏，重点在于**数据结构选择**、**工程化设计**和**状态机应用**的练手项目。

## 重构新增内容

本次重构重点添加了以下 C++ 面向对象核心知识点：

- [构造函数重载](#1-构造函数重载-constructor-overloading)
- [虚析构函数](#2-虚析构函数-virtual-destructor)
- [友元函数](#3-友元函数-friend-function)
- [动态关联](#4-动态关联-dynamic-binding)
- [虚基类](#5-虚基类-virtual-base-class)

## 功能

- **经典玩法与双轨控制**：支持方向键和 WASD 控制，同向连按可加速。
- **动态窗口与地图适配**：启动时自动检测当前控制台窗口大小，支持用户自定义地图宽高，并内置防越界自动裁剪保护。
- **状态机生命周期**：包含主菜单、游戏中、暂停、游戏结束完整状态流转。
- **防卡死食物生成**：后期蛇身变长时不会出现随机数死循环，全屏占满时触发"YOU WIN!"胜利判定。
- **极致渲染体验**：纯局部刷新，无 `system("cls")` 闪烁问题；结束自动恢复光标，默认支持 UTF-8 中文显示。

## 运行方法

### 编译
```bash
g++ -std=c++11 main.cpp game.cpp gameobject.cpp snake.cpp map.cpp -o snake.exe
```

或使用 CMake：
```bash
mkdir build && cd build
cmake ..
make
```

### 运行
```bash
snake.exe
```

### 环境要求

- Windows 操作系统
- MinGW / Visual Studio 编译器
- 控制台窗口建议不小于 50×25

## 操作说明

| 按键 | 功能 |
| --- | --- |
| `↑` `↓` `←` `→` | 移动方向（推荐，无输入法冲突） |
| `W` `A` `S` `D` | 移动方向（注意需在英文输入法下） |
| `空格 (Space)` | 暂停 / 恢复游戏 |
| 同向方向键 | 游戏加速 |
| 反向方向键 | 游戏减速（惩罚机制） |
| `?` (`Shift`+`/` ) | 游戏中途强制返回主菜单 |
| `X` | 退出游戏 / 在暂停页面退回菜单 |

## 技术实现与设计决策（面试准备）

**Q1：为什么用 `deque` 而不是 `vector` 或 `list`？**
- `vector` 头部插入时间复杂度为 O(n)，不适合频繁在头部操作的贪吃蛇场景。
- `list` 两端操作 O(1)，但内存不连续，对 CPU 缓存不友好，且每个节点多两个指针的内存开销。
- `deque` 两端操作 O(1)，内存分段连续，最完美契合贪吃蛇"头增尾减"的滑动需求。

**Q2：如何处理渲染闪烁与残影问题？**
- **防闪烁**：摒弃低效的全局清屏 `system("cls")`，使用 Windows API 的 `SetConsoleCursorPosition` 定位光标，只在有变化的地方输出字符。
- **清残影**：在 `logic()` 中删除蛇尾前，通过 `deleteAbletail = snake.back()` 记录旧尾巴位置。在 `draw()` 渲染时对该坐标输出一次空格 " " 进行精准擦除。

**Q3：游戏后期蛇身几乎占满全屏时，随机生成食物卡死怎么解决？**
- 放弃暴力的纯随机猜坐标（While死循环检测），采用**空间收集法**。
- 每次生成食物时，遍历地图排查蛇身，将所有空闲坐标存入 `std::vector<std::pair<int, int>> freeSpaces`。然后直接从 `freeSpaces` 中 `rand()` 选取一个下标。
- 此外，如果发现 `freeSpaces.empty()`，则顺理成章地触发"游戏胜利"逻辑。

**Q4：为什么引入枚举和状态机？**
- 游戏包含菜单、进行、暂停、结束等多个环节，使用 `enum GameState` 配合 `switch-case` 进行调度，让主函数 `main()` 逻辑极度精简。
- 各个状态封装为独立的函数（如 `showMenu`, `playing`, `isPause`, `gameEnd`），实现高内聚低耦合，方便后期维护和扩展。

## C++ 知识点详解

### 1. 构造函数重载 (Constructor Overloading)

**位置**：`game.h` (Game 类), `snake.h` (Snake 类), `gameobject.h` (Food 类)

**概念**：构造函数重载允许类定义多个同名构造函数，但参数列表不同。这提供了多种对象创建方式，适应不同场景的需求。

**代码示例**：
```cpp
class Game {
public:
    Game();                          // 默认构造函数
    Game(int w, int h);              // 带地图参数的构造函数
    Game(int w, int h, int speed);   // 带地图和速度的构造函数
};

// 使用示例：
Game game1;              // 默认大小
Game game2(80, 40);      // 自定义地图
Game game3(80, 40, 5);   // 自定义地图和速度
```

**重载规则**：
- 参数数量不同
- 参数类型不同
- 参数顺序不同

### 2. 虚析构函数 (Virtual Destructor)

**位置**：`gameobject.h` (GameObject 类), `snake.h` (Snake 类), `game.h` (Game 类)

**概念**：当类用作基类时，析构函数应该声明为 `virtual`。这样通过基类指针删除派生类对象时，会先调用派生类析构函数，再调用基类析构函数，确保资源正确释放。

**代码示例**：
```cpp
class GameObject {
public:
    virtual ~GameObject() = default;  // 虚析构函数
};

class Snake : virtual public GameObject {
public:
    virtual ~Snake() {  // 派生类虚析构函数
        body.clear();   // 清理资源
    }
};

// 安全删除：
GameObject* obj = new Snake();
delete obj;  // 正确调用 Snake::~Snake() 然后 GameObject::~GameObject()
```

**为什么重要**：
- 如果基类析构函数不是虚函数，通过基类指针删除派生类对象时，只会调用基类析构函数，导致派生类资源泄漏。

### 3. 友元函数 (Friend Function)

**位置**：`snake.h` (Snake 类), `gameobject.h` (Food 类)

**概念**：友元函数不是类的成员函数，但可以访问类的私有和保护成员。友元关系是单向的，不继承，不传递。

**代码示例**：
```cpp
class Snake {
private:
    std::deque<std::pair<int, int>> body;
    Direction dir;
    
public:
    // 声明友元类
    friend class Game;
    
    // 声明友元函数
    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);
};

// 友元函数实现 - 可以直接访问私有成员
std::ostream& operator<<(std::ostream& os, const Snake& snake) {
    os << "Snake length: " << snake.body.size();  // 访问私有成员 body
    return os;
}
```

**使用场景**：
- 运算符重载（如 `<<` 输出运算符）
- 需要访问私有数据的辅助函数
- 紧密耦合的类（如 Game 需要访问 Snake 内部状态）

### 4. 动态关联 (Dynamic Binding / Polymorphism)

**位置**：`gameobject.h` (GameObject 类), `game.h` (Game 类), `game.cpp` (Game::renderAllObjects)

**概念**：动态关联（动态绑定）是指程序运行时根据对象的实际类型，而不是指针/引用的声明类型，来决定调用哪个函数。这是多态的核心机制。

**代码示例**：
```cpp
class GameObject {
public:
    virtual void render() const = 0;  // 纯虚函数
    virtual std::pair<int, int> getPosition() const = 0;
};

class Snake : virtual public GameObject {
public:
    void render() const override { /* 蛇的渲染逻辑 */ }
    std::pair<int, int> getPosition() const override { return showHead(); }
};

class Food : virtual public GameObject {
public:
    void render() const override { /* 食物的渲染逻辑 */ }
    std::pair<int, int> getPosition() const override { return position; }
};

// 动态关联演示：
std::vector<std::shared_ptr<GameObject>> objects;
objects.push_back(std::make_shared<Snake>());
objects.push_back(std::make_shared<Food>());

for (const auto& obj : objects) {
    obj->render();  // 运行时根据实际类型调用 Snake::render 或 Food::render
}
```

**实现机制**：
- 编译器为每个包含虚函数的类创建虚函数表（vtable）
- 对象包含虚函数表指针（vptr）
- 运行时通过 vptr 查找正确的函数地址

### 5. 虚基类 (Virtual Base Class)

**位置**：`gameobject.h` (GameObject, IRenderable), `snake.h` (Snake 类)

**概念**：虚基类用于解决菱形继承问题（Diamond Problem）。当两个派生类继承自同一个基类，而第三个类又同时继承这两个派生类时，使用 virtual 继承可以确保基类在最终派生类中只有一份副本。

**代码示例**：
```cpp
class GameObject {  // 虚基类
public:
    virtual ~GameObject() = default;
    virtual void render() const = 0;
};

class IRenderable {  // 另一个虚基类
public:
    virtual ~IRenderable() = default;
    virtual char getRenderChar() const = 0;
};

// 使用虚继承
class Snake : virtual public GameObject, virtual public IRenderable {
public:
    void render() const override;
    char getRenderChar() const override;
};

class Food : virtual public GameObject, virtual public IRenderable {
public:
    void render() const override;
    char getRenderChar() const override;
};

// 如果存在这样的继承（演示菱形继承）：
class SpecialObject : public Snake, public Food {
    // 由于使用了虚继承，GameObject 和 IRenderable 只有一份副本
    // 避免了二义性和数据冗余
};
```

**菱形继承问题**：
```
     GameObject
    /          \
 Snake        Food
    \          /
     SpecialObject
```

**不使用虚继承的问题**：
- `SpecialObject` 会包含两份 `GameObject` 成员
- 访问 `GameObject` 成员时产生二义性
- 数据冗余，浪费内存

**使用虚继承的好处**：
- 基类成员在最终派生类中只有一份
- 由最终派生类负责初始化虚基类
- 避免访问冲突和数据冗余

## 项目结构

```text
SnakeGame/
├── main.cpp          # 程序入口
├── game.h            # 游戏类定义
├── game.cpp          # 游戏类实现
├── gameobject.h      # 游戏对象基类、虚基类、Food类
├── gameobject.cpp    # Food类实现
├── snake.h           # 蛇类定义
├── snake.cpp         # 蛇类实现
├── map.h             # 地图类（预留）
├── map.cpp           # 地图类（预留）
├── CMakeLists.txt    # CMake 构建配置
├── README.md         # 项目说明文档
└── .gitignore
```

## 待改进（TODO）

- [x] **分文件组织代码**：将代码拆分为多个文件提高可维护性。
- [ ] **最高分记录**：增加本地文件读写（如存入 `.dat` 或 `.json` 文件），实现最高分持久化保存。
- [ ] **交互优化**：拦截不合理的方向输入（如正在向右移动时，直接忽略向左的按键），而不是给予减速惩罚。

## 作者

Lpcyc

## 许可证

MIT
