#ifndef DOWNLOADTASK_H
#define DOWNLOADTASK_H


#include <QRunnable>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QDebug>
#include <QObject> // 确保包含 QObject 头文件

class MyClientSocket;

/*
继承自 QObject：这使得 DownloadTask 可以使用 Qt 的信号和槽机制。
继承自 QRunnable：这允许 DownloadTask 被提交给 QThreadPool 执行。
*/
class DownloadTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    /*
        包含要下载的音乐数据的 JSON 数组
    */
    DownloadTask(const QJsonArray &musicArray, MyClientSocket *socket);

    virtual void run() override;

signals:
    void downloadCompleted(const QByteArray &content);//当下载完成后，downloadCompleted 信号会发射，携带下载的内容

private:
    QJsonArray musicArray;// 保存音乐数据的JSON数组
    MyClientSocket *socket;// 用于网络操作的客户端套接字

};

#endif // DOWNLOADTASK_H

/*
出现这个问题QSocketNotifier: Socket notifiers cannot be enabled or disabled from another thread怎么解决

这个错误通常是由于在非主线程中尝试操作 Qt 的 GUI 或套接字相关的对象导致的。Qt 的 GUI 和某些套接字操作只能在主线程中进行，而不能在工作线程中操作。

要解决这个问题，您可以使用信号和槽机制将非主线程中的操作发送回主线程执行。特别是，如果您在工作线程中下载数据，应该在下载完成后通过信号将数据传递回主线程进行处理。


通过使用 DownloadTask 类，并在非主线程中处理下载请求，同时通过信号和槽机制将数据传回主线程，
我们可以避免 QSocketNotifier: Socket notifiers cannot be enabled or disabled from another thread 错误
*/
