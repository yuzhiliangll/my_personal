/*

*/
#include <iostream>
using namespace std;

// 船体零部件
// 船体
class ShipBody
{
public:
    virtual string getShipBody() = 0;
    virtual ~ShipBody() {}

};
// 这样，只要添加了新的造船材料，就给它添加一个对应的子类（父类是 ShipBody），在这个子类重写父类的虚函数getShipBody()，用这种材料把船体造出来就行了。
class WoodBody : public ShipBody
{
public:
    string getShipBody() override
    {
        return string("用<木材>制作轮船船体...");// 显示转换
    }
};

class IronBody : public ShipBody
{
public:
    string getShipBody() override
    {
        return string("用<钢铁>制作轮船船体...");
    }
};

class MetalBody : public ShipBody
{
public:
    string getShipBody() override
    {
        return string("用<合金>制作轮船船体...");
    }
};

/*
    知道了如何处理船体部分，那么动力和武器部分的处理思路也是一样的：

    可以给船提供不同的动力系统，因此这个属性是可变的，所以需要提供一个抽象类
    可以给船提供不同的武器系统，因此这个属性也是可变的，所以也需要提供一个抽象类
*/
// 引擎
class Engine
{
public:
    virtual string getEngine() = 0;
    virtual ~Engine() {}
};

class Human : public Engine
{
public:
    string getEngine() override
    {
        return string("使用<人力驱动>...");
    }
};

class Diesel : public Engine
{
public:
    string getEngine() override
    {
        return string("使用<内燃机驱动>...");
    }
};

class Nuclear : public Engine
{
public:
    string getEngine() override
    {
        return string("使用<核能驱动>...");
    }
};


// 武器
class Weapon
{
public:
    virtual string getWeapon() = 0;
    virtual ~Weapon() {}
};

class Gun : public Weapon
{
public:
    string getWeapon() override
    {
        return string("配备的武器是<枪>");
    }
};

class Cannon : public Weapon
{
public:
    string getWeapon() override
    {
        return string("配备的武器是<自动机关炮>");
    }
};

class Laser : public Weapon
{
public:
    string getWeapon() override
    {
        return string("配备的武器是<激光>");
    }
};

/*
    如果有了以上的零件，只需要在工厂中将它们装配到一起，这样就得到了一艘船，
    这是一艘什么型号的船取决于使用的是什么零件，所以只需要让这艘船对应一个类就可以了，这个类的定义如下：
*/
// 轮船类
class Ship
{
public:
    // 这艘船使用的零件是通过构造函数参数传递进来的，并在类的内部对这些零件对象进行了保存，这样在释放船这个对象的时候就可以将相应的零件对象一并析构了。
    Ship(ShipBody *body, Weapon *weapon, Engine *engine) : m_body(body), m_weapon(weapon), m_engine(engine)
    {

    }

    ~Ship()
    {
        delete m_body;
        delete m_weapon;
        delete m_engine;
    }

    string getProperty()
    {
        string info = m_body->getShipBody() + m_weapon->getWeapon() + m_engine->getEngine();
        return info;
    }


private:
    ShipBody *m_body = nullptr;
    Weapon *m_weapon = nullptr;
    Engine *m_engine = nullptr;
};

/*
    准备生产
    万事俱备，只剩建厂了。
    造船厂要生产三种型号的船，那么也就是至少需要三条生产线，
    所以对应的工厂类也就不止一个，处理思路还是一样的，提供一个抽象的基类，然后在它的子类中完成各种型号的船的组装，每个子类对应的就是一条生产线。
*/

// 工厂类 -- 抽象
class AbstractFactory
{
public:
    virtual Ship *createShip() = 0;
    virtual ~AbstractFactory() {}
};

class BasicFactory : public AbstractFactory
{
public:
    Ship* createShip() override
    {
        Ship* ship = new Ship(new WoodBody, new Gun, new Human);
        cout << "<基础型>战船生产完毕, 可以下水啦..." << endl;
        return ship;
    }
};

class StandardFactory : public AbstractFactory
{
public:
    Ship* createShip() override
    {
        Ship* ship = new Ship(new IronBody, new Cannon, new Diesel);
        cout << "<标准型>战船生产完毕, 可以下水啦..." << endl;
        return ship;
    }
};

class UltimateFactory : public AbstractFactory
{
public:
    Ship* createShip() override
    {
        Ship* ship = new Ship(new MetalBody, new Laser, new Nuclear);
        cout << "<旗舰型>战船生产完毕, 可以下水啦..." << endl;
        return ship;
    }
};

/*
    在这个图中有四个抽象类，分别是：

        ShipBody 类：船体的抽象类
        有三个子类，在子类中通过不同的材料来建造船体
        Weapon 类：武器的抽象类
        有三个子类，在子类中给战船提供不同种类的武器
        Engine 类：动力系统抽象类
        有三个子类，在子类中给战船提供不同动力系统
        AbstractFactory 类：抽象工厂类
        在子工厂类中生产不同型号的战船
        和ShipBody 、Weapon、Engine有依赖关系，在工厂函数中创建了它们的实例对象
        和Ship 类有依赖关系，在工厂函数中创建了它的实例对象
        关于Ship类它可以和ShipBody 、Weapon、Engine可以是聚合关系，也可以是组合关系：

        组合关系：析构Ship类对象的时候，也释放了ShipBody 、Weapon、Engine对象
        聚合关系：析构Ship类对象的时候，没有释放ShipBody 、Weapon、Engine对象
        在上面的Ship类的析构函数中做了释放操作，因此在UML中将它们之间描述为了组合关系。
*/
int main()
{
    // 下单为旗舰型海贼船
    AbstractFactory* factory = new UltimateFactory;
    Ship* ship = factory->createShip();
    cout << ship->getProperty() << endl;
    delete ship;
    delete factory;

    return 0;
}
/*
    关于简单工厂模式、工厂模式和抽象工厂模式的区别可以做如下总结：

        简单工厂模式不能遵守开放-封闭原则，工厂和抽象工厂模式可以
        简单工厂模式只有一个工厂类，工厂和抽象工厂有多个工厂类
        工厂模式创建的产品对象相对简单，抽象工厂模式创建的产品对象相对复杂
            工厂模式创建的对象对应的类不需要提供抽象类【这产品类组件中没有可变因素】
            抽象工厂模式创建的对象对应的类有抽象的基类【这个产品类组件中有可变因素】
*/



