#include <iostream>
#include "NewsAgency.h"
#include "Observer.h"


int main()
{
    // 创建新闻社对象
    Morgans* ms = new Morgans;//Morgans 和 Gossip 是 NewsAgency 类的子类对象。
    Gossip* gossip = new Gossip;

    // 创建订阅者对象，并将其与新闻社关联
    // 并且在构造函数中将自己注册到相应的新闻社对象中。
    Dragon* dragon = new Dragon("蒙奇·D·龙", ms);
    Shanks* shanks = new Shanks("香克斯", ms);
    Bartolomeo* barto = new Bartolomeo("巴托洛米奥", gossip);

    // 新闻社推送消息

    // 调用 notify 方法，将消息推送给所有订阅了该新闻社的订阅者
    ms->notify("蒙奇·D·路飞成为新世界的新的四皇之一, 赏金30亿贝里!!!");
    std::cout << "======================================" << std::endl;
    gossip->notify("女帝汉库克想要嫁给路飞, 给路飞生猴子, 哈哈哈...");

    // 释放资源
    delete ms;
    delete gossip;
    delete dragon;
    delete shanks;
    delete barto;

    return 0;
}

/*
    观察者模式的实现逻辑涉及以下几个核心部分：

    新闻社（NewsAgency）：

        维护一个观察者列表。
        提供添加（attach）和删除（detach）观察者的方法。
        定义一个纯虚函数 notify，用于通知所有观察者（具体的子类实现这个方法）。
    具体新闻社（Morgans 和 Gossip）：

        实现 notify 方法，将消息发送给所有注册的观察者。
    
    订阅者（Observer）：

        需要知道其关注的新闻社（NewsAgency）对象。
        提供一个纯虚函数 update，用于更新接收到的消息。
    
    具体订阅者（Dragon、Shanks 和 Bartolomeo）：

    实现 update 方法，根据接收到的消息进行具体操作（例如输出消息）。
*/
/*
    +---------------------+
    |    Observer         |<---------------------------------------------------+
    +---------------------+                                                    |
    | - m_name            |                                                    |
    | - m_news            |                                                    |
    | + update(msg)       |                                                    |
    | + unsubscribe()     |                                                    |
    +---------------------+                                                    |
            ^                                                             |
            |                                                             |
            |    +---------------------+                                    |
            |    |   Dragon             |                                    |
            |    +---------------------+                                    |
            |    | + update(msg)        |                                    |
            |    +---------------------+                                    |
            |                                                             |
            |    +---------------------+                                    |
            |    |   Shanks             |                                    |
            |    +---------------------+                                    |
            |    | + update(msg)        |                                    |
            |    +---------------------+                                    |
            |                                                             |
            |    +---------------------+                                    |
            |    |   Bartolomeo         |                                    |
            |    +---------------------+                                    |
            |    | + update(msg)        |                                    |
            |    +---------------------+                                    |
            |                                                             |
            |                                                             |
            |    +---------------------+                                    |
            |    |   NewsAgency         |                                    |
            |    +---------------------+                                    |
            |    | - m_list             |                                    |
            |    | + attach(Observer*)  |                                    |
            |    | + detach(Observer*)  |                                    |
            |    | + notify(std::string)|                                    |
            |    +---------------------+                                    |
            |           ^   ^   ^                                             |
            |           |   |   |                                             |
            |    +---------------------+                                    |
            |    |   Morgans            |                                    |
            |    +---------------------+                                    |
            |    | + notify(msg)        |                                    |
            |    +---------------------+                                    |
            |                                                             |
            |    +---------------------+                                    |
            |    |   Gossip             |                                    |
            |    +---------------------+                                    |
            |    | + notify(msg)        |                                    |
            |    +---------------------+                                    |
            |                                                             |
            |                                                             |
            |   +---------------------+                                    |
            |   |   main()             |                                    |
            |   +---------------------+                                    |
            |   | - Creates NewsAgency |                                    |
            |   | - Creates Observers  |                                    |
            |   | - Calls notify()     |                                    |
            |   +---------------------+                                    |
            |                                                             |
            +-------------------------------------------------------------+

 */

/*
    订阅者（Observer）：这是一个抽象类，定义了 update 方法用于接收和处理消息，并有一个 unsubscribe 方法用于取消订阅。

具体订阅者（Dragon、Shanks、Bartolomeo）：这些类实现了 Observer 的 update 方法，根据接收到的消息执行具体的操作。

新闻社（NewsAgency）：这是一个抽象类，管理观察者的添加、删除和通知功能，具体实现由其子类完成。

具体新闻社（Morgans 和 Gossip）：这些类实现了 NewsAgency 的 notify 方法，用于通知所有注册的观察者。

主函数（main）：创建新闻社对象和订阅者对象，将订阅者对象注册到新闻社，并调用 notify 方法来推送消息。
*/



