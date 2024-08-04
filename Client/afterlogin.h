#ifndef AFTERLOGIN_H
#define AFTERLOGIN_H

#include <QWidget>
#include <QtXml>
#include "myclientsocket.h"
#include "http.h"



namespace Ui {
class AfterLogin;
}


class AfterLogin : public QWidget
{
    Q_OBJECT

public:
    explicit AfterLogin(QWidget *parent = nullptr, MyClientSocket *socket = nullptr);
    ~AfterLogin();

    void setLoginInfo(const QString & username, const QString &nickname ,const QString& headerpath);//提取登陆过的信息

    void updateAvatarPathInXml(const QString &username, const QString &newAvatarPath);// 更新xml文件中的头像路径

public slots:
    void changeAvatar();// 改变头像
    void headerimageDataRecv(QByteArray array);// 头像数据接收

    void openMusicPlayer(); // 进入音乐播放器界面
    void OnlineMusic();// 进入在线音乐播放界面
    void openHTTP();// 进入AI界面



signals:



private slots:
    // 返回登录界面的槽函数
    void backclicked();


private:
    Ui::AfterLogin *ui;
    MyClientSocket *CSocket; //  必须要有：接收为传递过来的 MyClientSocket 指针
    QDomDocument doc; // xml文本对象--保证了整个 xml树的存活

};

#endif // AFTERLOGIN_H
