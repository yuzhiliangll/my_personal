#ifndef MYCLIENTSOCKET_H
#define MYCLIENTSOCKET_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QTimer> // 包含 QTimer 头文件


struct MyClientSocketPrivate;

class MyClientSocket : public QObject // 一个类  最小责任
{
    Q_OBJECT//宏--使类可以使用信号和槽
public:
    explicit MyClientSocket(QObject * parent = nullptr);
    void Connect(const QString& serverIP, const int &port);

    ~MyClientSocket();

    // --------发送数据到服务器
    void sendData(const QByteArray &data);

signals:// ---通过 emit 关键字来发射（emit），允许其他部分连接（connect）到这些信号并作出响应
    // 函数声明
    void Connected();// 连接成功信号
    void Disconnected();// 断开连接信号

    // 信号可以带参数
    void DataRecv(QByteArray array);

public slots:

    void reconnect(); // 定义一个槽函数来处理断线重连


private:
    MyClientSocketPrivate *p;
    QTimer *reconnectTimer; // 在私有成员中声明 QTimer
    bool isConnected; // 连接状态标志


};

#endif // MYCLIENTSOCKET_H
