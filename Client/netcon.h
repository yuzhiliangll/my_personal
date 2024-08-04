#ifndef NETCON_H
#define NETCON_H

#include <QWidget>
#include "myclientsocket.h"
#include <QtXml>
#include <QCloseEvent> // 确保包含头文件

namespace Ui {
class NetCon;
}

class NetCon : public QWidget
{
    Q_OBJECT

public:
    explicit NetCon(QWidget *parent = nullptr, MyClientSocket *socket = nullptr);
    ~NetCon();

signals:
    void connectionInfoChanged(const QString &ip, int port); // 触发IP地址改变的信号

public slots:
    void onCancelButtonClicked();// 返回主界面

private:
    Ui::NetCon *ui;

    MyClientSocket *cSocket; //  必须要有：接收为传递过来的 MyClientSocket 指针

    QDomDocument doc; // xml文本对象--保证了整个 xml树的存活
};

#endif // NETCON_H
