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

// 定义工厂类
/*
    强枚举类型：enum class 是 C++11 引入的强类型枚举，具有类型安全性，避免了传统枚举中可能出现的隐式转换问题。
类型检查：由于是强枚举类型，Type 的值必须通过 Type::Sheep、Type::Lion 等方式来使用，确保了类型的安全性和代码的可读性。
 */
enum class Type:char{Sheep, Lion, Bat};// 定义强枚举类型-- 相比 宏 来说 会有类型检查
class SmileFactory
{
public:
    // 返回值指定为 父类类型
    /*
        工厂函数createSmile(Type type)的返回值修改成了AbstractSmile*类型，这是一个指向抽象基类 AbstractSmile 的指针。由于返回的是基类指针，实际指向的对象可以是任意派生类（如 SheepSmile、LionSmile、BatSmile）的实例，这种机制实现了多态。通过这个指针保存的是子类对象的地址，这样就实现了多态，
        所以在main()函数中，通过obj对象调用的实际是子类BatSmile中的函数，
    */
    AbstractSmile* createSmile(Type type)// 这样写是 用父类的指针指向子类对象-- 多态
    {
        AbstractSmile* ptr = nullptr;
        //类型检查与对象创建
        switch (type)
        {
        case Type::Sheep:
            ptr = new SheepSmile;// 并将其地址赋值给 ptr
            break;
        case Type::Lion:
            ptr = new LionSmile;
            break;
        case Type::Bat:
            ptr = new BatSmile;
            break;
        default:
            break;
        }
        return ptr;
    }

};


int main(int argc, char *argv[])
{
    SmileFactory* factory = new SmileFactory;
    AbstractSmile* obj = factory->createSmile(Type::Lion);
    obj->transform();
    obj->ability();
    delete obj;
    delete factory;
    return 0;
}


