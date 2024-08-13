#ifndef __NEWS_AGENCY_H__
#define __NEWS_AGENCY_H__

#include <list>
#include <string>


// 声明订阅者类, 只是做了声明,  并没有实现包含这个类的头文件
class Observer; // 声明订阅者类--此处只是做一个声明，让编译器能够通过编译

// 新闻社
class NewsAgency
{
public:
    void attach(Observer* ob);// 添加
    void detach(Observer* ob);// 删除

    virtual void notify(std::string msg) = 0;// 通知消息发送给 所有的订阅者
    virtual ~NewsAgency() {};

protected:
    // 订阅者列表-- 将所有的订阅者都存储到这个列表中
    std::list<Observer*> m_list;

};

// 摩根斯的新闻社可以作为上面NewsAgency 类的子类，在子类中重写父类的纯虚函数notify()方法就可以了。
class Morgans : public NewsAgency
{
public:
    void notify(std::string msg) override;

};

// 八卦新闻
class Gossip : public NewsAgency
{
public:
    void notify(std::string msg) override;
};




#endif // __NEWS_AGENCY_H__
