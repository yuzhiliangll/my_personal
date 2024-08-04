#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include "myclientsocket.h"
#include "signup.h"
#include <QtXml>
#include <QFile>
#include <QListWidget>
#include "netcon.h"
#include "afterlogin.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    MyClientSocket* getClientSocket() const; // 20240701----添加获取 MyClientSocket 指针的方法---md好像用不到

    // 添加账号信息到account.xml中
    void addAccountIntoXml(const QString &filePath, const QString &account, const QString &username, const QString &avatarPath, bool rememberPassword);
    bool readRememberPasswordFromXml(const QString &username);// 从 XML 文件中读取记住密码标志位的函数


    ~Widget();

    // 公有方法---界面控件使用权
    void disableControls();
    void enableControls();

signals:// 定义信号
    void LoginSuccess();// 登录成功后的信号


// 槽函数的声明
public slots:

    void Login();// 登陆处理
    void initializeAccountMap();// 初始化登陆列表项
    // void LoginInfoChanged();// 登录信息改变
    void rememberPasswordChanged(int state);// 添加新的槽函数 rememberPasswordChanged 来处理记住密码的状态改变


    void handleDataRecv(QByteArray array);// 接受数据处理


    void PasswordStatusFlipped(); // 密码显示状态
    void pushButton_SignUp();// 注册界面跳转

    void pushButton_NetCon();// 网络配置界面跳转



private slots:
    void updateConnectionInfo(const QString &ip, int port); // 添加声明
    void openAfterLoginWindow();// 打开登录之后的新窗口


private:
    Ui::Widget *ui;
    // QTcpSocket *c;
    bool isPasswordVisible; // 用于跟踪密码是否可见
    QByteArray buffer;// 自定义缓冲区

    MyClientSocket *c;// 添加：使用自定义的MyClientSocket 成员变量


    QDomDocument doc; // xml文本对象--保证了整个 xml树的存活    
    QListWidget *w;// 用于显示登陆过的账号的界面
    std::map<QString, QDomNode> AccountMap;//用于存储账号信息。这里的键是 QString 类型的账号名，值是 QDomNode 类型，表示对应的 XML 节点

    NetCon * netconwidget;// 网络配置窗口对象
    AfterLogin *afterwidget;// 登录成功之后


private:
    QString xmlFilePath = R"(C:\Users\21196\Desktop\QTnote_lv\20140702_xml\account.xml)";
    QString headerimagepath = ":/images/header_image.png";

    bool rememberPassword = false;// 修改 SignUp.h 文件，添加一个新的私有变量用于存储记住密码的状态

    QString currentUsername;// 添加保存当前账号的变量
    QString currentAvatarPath;// 添加保存当前头像路径的变量
    QString currentNickname;// 添加保存当前用户昵称的变量
    QString readNickname(const QString &username);// 添加读取用户昵称的函数
    QString readAvatarPath(const QString &username); // 添加读取头像路径的函数--方便跳转另一个界面后进行头像更换
};

#endif // WIDGET_H
