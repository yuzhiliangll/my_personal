#include "myclientsocket.h"
#include <QTcpSocket>
#include <memory>
#include <QDebug>
#include <QMessageBox>

using SocketPtr = std::unique_ptr<QTcpSocket>;


#pragma pack(push, 4) // 告诉编译器按照4字节对齐
// 客户端套接字类 MyClientSocket
struct  MyClientSocketPrivate
{
    MyClientSocketPrivate():c(new QTcpSocket), ip(""), port(0){}
    SocketPtr c ;      // 使用 unique_ptr 管理 QTcpSocket 对象
    QByteArray buffer; // 用于存储从套接字读取的数据
    QString ip;
    int port;
};
#pragma pack(pop) // 恢复默认对齐方式

MyClientSocket::MyClientSocket(QObject *parent) : QObject(parent), p(new MyClientSocketPrivate), isConnected(false)
{
    reconnectTimer = new QTimer(this);// 定时器

    // 连接成功
    connect(p->c.get(), &QTcpSocket::connected, [this]()
    {
        qDebug()<< "connect success!====\n";
        if (!isConnected)
        {
            isConnected = true; // 更新连接状态标志位
            emit Connected();   // 发送自定义连接成功信号
        }
    });

    // 断开的时候连接处理
    connect(p->c.get(), &QTcpSocket::disconnected, [this]()
    {
        // 启动断线重连定时器
        reconnectTimer->start(5000); // 每隔5秒尝试重连
        // 发出断开连接信号
        emit Disconnected();
        isConnected = false;// 断开连接时更新连接状态

    });

    // 处理连接错误

     // 定时器超时信号与重连函数的连接
    connect(reconnectTimer, &QTimer::timeout, this, &MyClientSocket::reconnect);

    // 读取数据处理
    // 数据读取事件
    // readyRead 信号：不是服务器发送一次数据就触发一次信号 --- 有缓冲区
    connect(p->c.get(), &QTcpSocket::readyRead, [this]()
    {
        p->buffer.append(p->c->readAll());// 将tcp缓冲区的可读数据加入到我们自己的缓冲区

        while(1)
        {
            // 读取的数据量不够一个包头则直接返回，等待下一次读取
            while(static_cast<size_t>(p->buffer.size()) < sizeof(size_t))// static_cast<size_t> 将 p->buffer.size() 转换为 size_t 类型
            {
                return;
            }
            size_t size = 0;
            // 取出包头
            memcpy(&size, p->buffer.data(), sizeof(size_t));
            // 我们缓冲区的数据量 达不到 包头 + 数据正文  等待下一次读取
            if(static_cast<size_t>(p->buffer.size()) < size + sizeof(size_t))
            {
                return;
            }
            // 触发数据接收信号，提取数据包的正文部分，以便上层应用可以处理
            emit DataRecv(p->buffer.mid(static_cast<int>(sizeof(size_t)), static_cast<int>(size)));// 一整包数据

            p->buffer.remove(0,  static_cast<int>(sizeof(size_t) + size));// 删除一包数据 (包头 + 正文)--以便下一次循环可以继续处理新的数据包
        }
    });
}

// 连接服务器
void MyClientSocket::Connect(const QString &serverIP, const int &port)
{
    if (p->c->state() == QAbstractSocket::UnconnectedState)
    {
        p->c->connectToHost(serverIP, static_cast<quint16>(port));
        p->ip = serverIP;
        p->port = port;
    }
//    p->c->connectToHost(serverIP, static_cast<quint16>(port));
//    p->ip = serverIP;
//    p->port = port;
}


// 断线重连
void MyClientSocket::reconnect()
{
    if(isConnected == false)
    {
        qDebug()<<" waiting_reconnect......\n";
        p->c->connectToHost(p->ip, static_cast<quint16>(p->port));
    }
}

// ------
void MyClientSocket::sendData(const QByteArray &data)
{
    if (p->c->state() == QAbstractSocket::ConnectedState)
    {
//        qint64 size = data.size();
//        QByteArray content = data;
//        content.insert(0, (char *)&size, sizeof(size_t));
        // 发送数据到服务器
        p->c->write(data);
    }
    else
    {
        qDebug() << "Socket is not connected. Unable to send data.";
        // 可以在这里添加处理逻辑，例如重新连接等
    }
}


MyClientSocket::~MyClientSocket()
{
    delete p;
    delete reconnectTimer;// 释放定时器
}
