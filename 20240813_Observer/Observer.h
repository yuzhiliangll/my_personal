#pragma once

#include <string>
#include <iostream>
#include "NewsAgency.h"
// using namespace std;

// 抽象的订阅者类
class Observer
{
public:
    Observer(std::string name, NewsAgency* news) : m_name(name), m_news(news)// 需要通过构造函数给观察者提供一个信息发布者
    {
        m_news->attach(this);// 通过发布者对象将观察者对象存储了起来，这样就可以收到发布者推送的消息了。
    }

    void unsubscribe()// 观察者取消订阅, 将不再收到发布者推送的消息
    {
        m_news->detach(this);// 
    }

    virtual void update(std::string msg) = 0;// 观察者得到最新消息之后，用于更新自己当前的状态。
    virtual ~Observer() {}

private:
    std::string m_name;
    NewsAgency* m_news;
};

class Dragon : public Observer
{
public:
    using Observer::Observer;
    void update(std::string msg) override
    {
        std::cout << "@@@路飞的老爸革命军龙收到消息: " << msg << std::endl;
    }
};

class Shanks : public Observer
{
public:
    using Observer::Observer;
    void update(std::string msg) override
    {
        std::cout << "@@@路飞的引路人红发香克斯收到消息: " << msg << std::endl;
    }
};

class Bartolomeo : public Observer
{
public:
    using Observer::Observer;
    void update(std::string msg) override
    {
        std::cout << "@@@路飞的头号粉丝巴托洛米奥收到消息: " << msg << std::endl;
    }
};



