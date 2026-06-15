#pragma once
#include <utility>
#include <iostream>

// ============================================
// 知识点：虚基类 (Virtual Base Class)
// --------------------------------------------
// 虚基类用于解决菱形继承问题（Diamond Problem）。
// 当两个派生类继承自同一个基类，而第三个类又同时继承这两个派生类时，
// 如果不使用虚继承，会导致基类在最终派生类中存在两份副本，产生二义性。
// 
// 使用 virtual 继承后，虚基类的成员在最终派生类中只有一份副本，
// 由最终派生类负责初始化，避免了数据冗余和访问冲突。
// ============================================

class GameObject {
public:
    // 虚析构函数 - 知识点：确保通过基类指针删除派生类对象时正确释放资源
    virtual ~GameObject() = default;
    
    // 纯虚函数 - 知识点：动态关联（Dynamic Binding）
    // 虚函数允许运行时根据对象的实际类型调用对应的函数实现，
    // 而不是在编译时根据指针类型决定。这是多态的核心机制。
    virtual void render() const = 0;
    virtual std::pair<int, int> getPosition() const = 0;
    virtual bool isAtPosition(int x, int y) const = 0;
};

// 可渲染接口 - 使用虚继承避免菱形继承问题
class IRenderable {
public:
    virtual ~IRenderable() = default;
    virtual char getRenderChar() const = 0;
};

// 食物类 - 使用虚继承自GameObject和IRenderable
class Food : virtual public GameObject, virtual public IRenderable {
private:
    std::pair<int, int> position;
    char renderChar = 'F';
    
public:
    // 构造函数重载 - 知识点：同名函数通过参数列表不同实现不同初始化方式
    Food(); // 默认构造函数
    Food(int x, int y); // 带坐标参数的构造函数
    Food(int x, int y, char customChar); // 带坐标和自定义字符的构造函数
    
    ~Food() override = default;
    
    void render() const override;
    std::pair<int, int> getPosition() const override;
    bool isAtPosition(int x, int y) const override;
    char getRenderChar() const override;
    
    void setPosition(int x, int y);
    
    // 友元函数声明 - 知识点：允许非成员函数访问类的私有/保护成员
    // 友元函数打破了封装，但提供了灵活的访问控制，常用于运算符重载
    friend std::ostream& operator<<(std::ostream& os, const Food& food);
};

// 蛇类前置声明
class Snake;
