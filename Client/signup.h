#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include "myclientsocket.h"
#include <QFile>
#include <QtXml>

namespace Ui {
class SignUp;
}

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr, MyClientSocket *socket = nullptr);// 在 SignUp 类的构造函数中添加一个参数，用于接收 MyClientSocket 对象
    ~SignUp();

// 槽函数的声明
public slots:
    void SignUpPassword1StatusFlipped(); // 密码1显示状态
    void SignUpPassword2StatusFlipped(); // 密码2显示状态

    // 用户需知阅读状态翻转
    void readFlipped();

    // 处理数据接收
    void handleDataReceived(QByteArray array);


    void SignUpButtonClicked(); // 注册按钮点击事件
    void addAccountIntoXml(const QString &filePath, const QString &account, const QString &username, const QString &avatarPath);//添加账号信息到SignUpInfo.xml中

private slots:
    void backtomain();// 返回主界面

private:
    Ui::SignUp *ui;
    bool isSignUpPassword1Visible; // 用于跟踪密码1是否可见
    bool isSignUpPassword2Visible; // 用于跟踪密码2是否可见

    MyClientSocket *clientSocket; //  必须要有：接收为传递过来的 MyClientSocket 指针


    QDomDocument doc; // xml文本对象--保证了整个 xml树的存活
    // 注册信息保存
    QString SignUpInfoPath = R"(C:\Users\21196\Desktop\QTnote_lv\20140702_xml\SignUpInfo.xml)";
    QString SignUpImagePath = ":/images/header_image.png";

};


//添加一个函数将Base64编码字符串转换为QByteArray
QByteArray decodeBase64Image(const QString &base64);

#endif // SIGNUP_H
