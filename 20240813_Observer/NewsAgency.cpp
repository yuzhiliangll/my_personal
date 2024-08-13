#include <iostream>
#include "Observer.h"
#include "NewsAgency.h"

void NewsAgency::attach(Observer* ob)
{
    m_list.push_back(ob);
}

void NewsAgency::detach(Observer* ob)
{
    m_list.remove(ob);
}

/**********************************************************/
void Morgans::notify(std::string msg)
{
    std::cout << "摩根斯新闻社报纸的订阅者一共有<" << m_list.size() << ">人" << std::endl;
    for(const auto& item : m_list)
    {
        item->update(msg);// 订阅者类的定义在下面
    }
}

void Gossip::notify(std::string msg)
{
    std::cout << "八卦新闻社报纸的订阅者一共有<" << m_list.size() << ">人" << std::endl;
    for (const auto& item : m_list)
    {
        item->update(msg);
    }
}


