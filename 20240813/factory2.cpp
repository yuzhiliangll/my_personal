/*
    1. 简单工厂模式的弊端
    在上一节简单工厂模式中，创建了一个工厂类，用于生产需要的对象，
    但是这种方式有一个弊端，
    它违反了设计模式中的开放-封闭原则，先来看相关的代码：

    在上面的工厂函数中需要生成三种人造恶魔果实，现在如果想要生成更多，那么就需要在工厂函数的switch语句中添加更多的case，很明显这违背了封闭原则，也就意味着需要基于开放原则来解决这个问题。

使用工厂模式可以很完美的解决上述的问题，简单工厂模式是只有一个工厂类，而工厂模式是有很多的工厂类：

    一个基类，包含一个虚工厂函数，用于实现多态。
    多个子类，重写父类的工厂函数。每个子工厂类负责生产一种恶魔果实，这相当于再次解耦，
    将工厂类的职责再次拆分、细化，如果要生产新品种的恶魔果实，那么只需要添加对应的工厂类，无需修改原有的代码。

*/
#include <iostream>
using namespace std;


// 产品类的父类 -- 人造恶魔果实
class AbstractSmile
{
public:
    virtual void transform() = 0;// 必须在子类中重写
    virtual void ability() = 0;

    virtual ~AbstractSmile() {} // 虚析构函数-- 在多继承/多态的时候，防止内存泄漏--会判断释放的是子类对象还是父类对象

private: 


};

// 具体产品类 SheepSmile, LionSmile, BatSmile
class SheepSmile : public AbstractSmile
{
public:
    void transform() override
    {
        cout << "变成人兽 -- 山羊人形态..." << endl;
    }
    void ability() override
    {
        cout << "将手臂变成绵羊角的招式 -- 巨羊角" << endl;
    }

private: 
};

// 人造恶魔果实· 狮子形态
class LionSmile : public AbstractSmile
{
public:
    void transform() override
    {
        cout << "变成人兽 -- 狮子人形态..." << endl;
    }
    void ability() override
    {
        cout << "火遁· 豪火球之术..." << endl;
    }
};

class BatSmile : public AbstractSmile
{
public:
    void transform() override
    {
        cout << "变成人兽 -- 蝙蝠人形态..." << endl;
    }
    void ability() override
    {
        cout << "声纳引箭之万剑归宗..." << endl;
    }
};

// 定义工厂类的父类 AbstractFactory
class AbstractFactory
{
public:
    virtual AbstractSmile* createSmile() = 0;// 抽象方法，子类必须实现这个函数来创建具体的产品对象。
    virtual ~AbstractFactory() {}// 虚析构函数
    /*
        添加虚析构函数的目的是为了 确保在使用基类指针删除派生类对象时，能够正确调用派生类的析构函数，从而避免资源泄漏或未释放内存。
        为什么需要虚析构函数？
        当你通过基类指针删除一个派生类对象时，如果基类的析构函数不是虚函数，
        那么只会调用基类的析构函数，而不会调用派生类的析构函数。
        这可能导致派生类中分配的资源（例如内存、文件句柄等）无法正确释放，进而导致资源泄漏。
    */
};

class SheepFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile() override
    {
        return new SheepSmile;// 生产对象
    }
    ~SheepFactory()
    {
        std::cout << "释放 SheepFactory 类相关的内存资源" << std::endl;
    }
};

class LionFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile() override
    {
        return new LionSmile;// 生产对象
    }
    ~LionFactory()
    {
        cout << "释放 LionFactory 类相关的内存资源" << endl;
    }

};

class BatFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile() override
    {
        return new BatSmile;// 生产对象
    }
    ~BatFactory()
    {
        cout << "释放 BatFactory 类相关的内存资源" << endl;
    }
};


int main(int argc, char *argv[])
{
    AbstractFactory* factory = new LionFactory;// 基类指针 factory 创建了一个 LionFactory 实例。
    AbstractSmile* obj = factory->createSmile();// 使用 LionFactory 创建了一个 LionSmile 对象，并通过 AbstractSmile 的基类指针 obj 进行操作
    /*
            +-----------------+          +-------------------+
            |  AbstractFactory|          |  AbstractSmile    |
            |  *factory       |          |  *obj             |
            +-----------------+          +-------------------+
                    ^                             ^
                    |                             |
                    |                             |
            +-----------------+          +-------------------+
            |   LionFactory   | -------->|   LionSmile       |
            +-----------------+          +-------------------+
            | createSmile()   |          | transform()       |
            +-----------------+          | ability()         |
                                         +-------------------+
            工作流程：
            先创建 LionFactory 对象并将其地址赋给 factory。
            然后通过 factory->createSmile() 创建 LionSmile 对象，并将其地址赋给 obj。
            通过 obj 来操作 LionSmile 对象。

    */
    obj->transform();
    obj->ability();
    delete obj;
    delete factory;
    return 0;
}
// 工厂模式就是对 简单工厂模式的优化, 优化了 生产对象的工厂部分
/*
    不论是恶魔果实的基类，还是工厂类的基类，
    它们的虚函数可以是纯虚函数，也可以是非纯虚函数。
    这样的基类在设计模式中就可以称之为抽象类（此处的抽象类和C++中对抽象类的定义有一点出入）。
*/

