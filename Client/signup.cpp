#include "signup.h"
#include "ui_signup.h"
#include "widget.h"
#include "myclientsocket.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>

SignUp::SignUp(QWidget *parent, MyClientSocket *socket) :
    QMainWindow(parent),
    ui(new Ui::SignUp),
    isSignUpPassword1Visible(false),
    isSignUpPassword2Visible(false),
    clientSocket(socket) // 初始化 clientSocket----也就是接收传过来的套接字
{
    ui->setupUi(this);
    // qDebug() << "上一级界面地址 : "<< this->parentWidget();

    // 有一个 QPushButton 用于切换密码显示状态
    // 设置密码输入框初始状态为隐藏
    ui->lineEdit_passwd1->setEchoMode(QLineEdit::Password);
    ui->lineEdit_passwd2->setEchoMode(QLineEdit::Password);
    ui->pushButton_unseenSignUp_1->setIcon(QIcon(":/images/Unseen.png"));// 隐藏密码
    ui->pushButton_unseenSignUp_2->setIcon(QIcon(":/images/Unseen.png"));// 隐藏密码
    connect(ui->pushButton_unseenSignUp_1, &QPushButton::clicked, this, &SignUp::SignUpPassword1StatusFlipped);
    connect(ui->pushButton_unseenSignUp_2, &QPushButton::clicked, this, &SignUp::SignUpPassword2StatusFlipped);


    // 设置用户需知链接
    ui->label_readme->setText("<font>我已阅读\
                                    <a href='https://raw.githubusercontent.com/yuzhiliangll/my_personal/main/uesr_notify_yzl.html'>《用户需知》</a>\
                                    并同意其中所有内容</font>");
    // 允许打开外部链接
    ui->label_readme->setOpenExternalLinks(true);
    // 用户需知勾选状态UI变化
    connect(ui->checkBox_indicator, &QCheckBox::stateChanged, this, &SignUp::readFlipped);

    // 返回按钮
    connect(ui->backtomain, &QPushButton::clicked, this, &SignUp::backtomain);
    // 最终注册按钮
    connect(ui->pushButton_signupfinal, &QPushButton::clicked, this, &SignUp::SignUpButtonClicked); // 注册按钮点击事件

    // 数据接收处理
    connect(clientSocket, &MyClientSocket::DataRecv, this, &SignUp::handleDataReceived);

}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::SignUpPassword1StatusFlipped()
{
    if(isSignUpPassword1Visible)
    {
        ui->lineEdit_passwd1->setEchoMode(QLineEdit::Password);
        ui->pushButton_unseenSignUp_1->setIcon(QIcon(":/images/Unseen.png"));// 隐藏密码
    }
    else
    {
        ui->lineEdit_passwd1->setEchoMode(QLineEdit::Normal);
        ui->pushButton_unseenSignUp_1->setIcon(QIcon(":/images/Seen.png"));// 显示
    }
    isSignUpPassword1Visible = !isSignUpPassword1Visible; // 切换状态
}

void SignUp::SignUpPassword2StatusFlipped()
{
    if(isSignUpPassword2Visible)
    {
        ui->lineEdit_passwd2->setEchoMode(QLineEdit::Password);
        ui->pushButton_unseenSignUp_2->setIcon(QIcon(":/images/Unseen.png"));// 隐藏密码
    }
    else
    {
        ui->lineEdit_passwd2->setEchoMode(QLineEdit::Normal);
        ui->pushButton_unseenSignUp_2->setIcon(QIcon(":/images/Seen.png"));// 显示
    }
    isSignUpPassword2Visible = !isSignUpPassword2Visible; // 切换状态
}

// 用户需知阅读状态翻转
void SignUp::readFlipped()
{
    if (ui->checkBox_indicator->isChecked())
    {
        ui->checkBox_indicator->setStyleSheet("QCheckBox::checkBox_indicator\
                                               { border: 1px solid black;\
                                                 width: 14px;\
                                                 height: 14px;\
                                                 border-radius: 8px;\
                                                 background-color: rgb(0, 95, 184); }");
    }
    else
    {

        ui->checkBox_indicator->setStyleSheet("QCheckBox::checkBox_indicator\
                                               { border: 1px solid black;\
                                                 width: 14px;\
                                                 height: 14px;\
                                                 border-radius: 8px;\
                                                 background-color: white; }");
    }
}


void SignUp::SignUpButtonClicked()
{
    QString nickname = ui->lineEdit_nickname->text();
    QString username = ui->lineEdit_account1->text();
    QString password = ui->lineEdit_passwd1->text();
    QString password1 = ui->lineEdit_passwd2->text();

    // 简单的前端验证
    if (nickname.isEmpty() || username.isEmpty() || password.isEmpty() || password1.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请填写完整信息！");
        return;
    }

    if (password != password1)
    {
        QMessageBox::warning(this, "警告", "两次输入的密码不一致！");
        return;
    }

    // 判断是否勾选了已读条款
    if (!(ui->checkBox_indicator->isChecked()))
    {
        QMessageBox::warning(this, "注册失败", "请阅读用户需知并勾选已读");
        return;
    }

    // 创建 JSON 对象
    QJsonObject obj;
    obj["username"] = username;
    obj["passwd"] = password;
    obj["request"] = "SignUp";
    obj["nickname"] = nickname;

    // 将 JSON 对象转换为 QByteArray
    QByteArray content = QJsonDocument(obj).toJson();
    size_t size = static_cast<size_t>(content.size());
    content.insert(0, reinterpret_cast<const char*>(&size), sizeof(size_t));

    // -----使用 MyClientSocket 发送注册请求

    clientSocket->sendData(content); //  MyClientSocket 中有一个 sendData 方法用于发送数据

}

//添加账号信息到SignUpInfo.xml中
void SignUp::addAccountIntoXml(const QString &filePath, const QString &account, const QString &username, const QString &avatarPath)
{
    QDomDocument doc;
    // XML文件路径

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly) == false)
    {
        qDebug()<<"文件打开失败\n";
    }

    auto content = file.readAll();
    file.close();// 读完后关闭

    QString errorMsg; // 错误信息
    int line, column; // 行 列
    if (doc.setContent(content, &errorMsg, &line, &column) == false)
    {
       qDebug() << "line : " << line << "column : " << column << "errormsg : " << errorMsg << endl;
       return;
    }
    qDebug() << "xml解析成功!\n";

    // 获取根元素
    QDomElement root = doc.documentElement(); // 返回 XML 文档的根元素
    // 检查是否已经存在相同账号的元素
    QDomNodeList accounts = root.elementsByTagName("账号"); // 返回文档中所有与指定标签名匹配的元素
    for (int i = 0; i < accounts.count(); ++i) // 遍历 accounts 中的每一个元素
    {
        QDomElement existingAccount = accounts.at(i).toElement(); // 返回当前索引 i 处的节点，使用 .toElement() 将其转换为 QDomElement 类型 existingAccount
        if (existingAccount.attribute("账号") == account) // 获取 existingAccount 元素的 "账号" 属性的值
        {
            qDebug() << "账号已存在，不需要重复添加!";
            return;
        }
    }

    // 创建新的账号元素
    QDomElement accountElement = doc.createElement("账号");
    accountElement.setAttribute("账号", account);
    accountElement.setAttribute("用户名", username);
    accountElement.setAttribute("头像", avatarPath);

    // 将账号元素添加到根元素中
    root.appendChild(accountElement);
    // 保存 XML 文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "无法打开 XML 文件进行写入！\n";
        return;
    }
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
    qDebug() << "账号信息已成功添加到 XML 文件！\n";
}

//添加一个函数将Base64编码字符串转换为QByteArray
QByteArray decodeBase64Image(const QString &base64)
{
    return QByteArray::fromBase64(base64.toUtf8());
}


// 处理数据接收
void SignUp::handleDataReceived(QByteArray array)
{
    QJsonDocument doc = QJsonDocument::fromJson(array);// 将一个JSON格式的字节数组（array）转换为一个QJsonDocument对象
    QJsonObject obj = doc.object();                    // 从QJsonDocument对象doc中提取一个QJsonObject对象
    QString response = obj["response"].toString();

    // 获取用户名--用于创建文件夹
    QString username = ui->lineEdit_account1->text();

    if (response == "sign up success")
    {
        QMessageBox::information(this, "提示", "注册成功_请返回主界面");

        // 在注册成功后创建用户相关文件夹并保存默认头像
        QString folderPath = QDir::currentPath() + "/Localfolder/" + username + "/headerimages";//确保文件夹路径是从根目录开始的绝对路径，而不是相对路径。这样可以避免由于相对路径解析不正确而导致嵌套文件夹的问题
        QString musicPath = QDir::currentPath() + "/Localfolder/" + username + "/music_resources";
        QDir headerImagesDir(folderPath);
        QDir musicResourcesDir(musicPath);
        bool headerImagesCreated = true;
        bool musicResourcesCreated = true;
        if (!headerImagesDir.exists())
        {
            headerImagesCreated = headerImagesDir.mkpath(folderPath);
        }
        if (!musicResourcesDir.exists())
        {
            musicResourcesCreated = musicResourcesDir.mkpath(musicPath);
        }
        if (!headerImagesCreated || !musicResourcesCreated)
        {
            QString errorMsg = "文件夹创建失败: ";
            if (!headerImagesCreated) {
                errorMsg += folderPath + " ";
            }
            if (!musicResourcesCreated) {
                errorMsg += musicPath;
            }
            QMessageBox::warning(this, "警告", errorMsg);
            return;
        }
        qDebug() << "Header Images Folder path:" << folderPath;
        qDebug() << "Music Resources Folder path:" << musicPath;

        // 获取Base64编码的头像数据
        QString avatarBase64 = obj["avatar"].toString();
        QByteArray avatarData = decodeBase64Image(avatarBase64);// 解码后的数据
        // 保存头像数据到本地
        QString avatarFilePath = folderPath + "/headerimage.png";
        QFile avatarFile(avatarFilePath);
        if(avatarFile.open(QIODevice::WriteOnly))
        {
            avatarFile.write(avatarData);
            avatarFile.close();
            qDebug() << "头像保存成功:" << avatarFilePath;
        }
        else
        {
            QMessageBox::warning(this, "警告", "头像保存失败" + avatarFilePath);
            return;
        }
        // 保存账号信息到 XML 文件
        addAccountIntoXml(SignUpInfoPath, ui->lineEdit_account1->text(), ui->lineEdit_nickname->text(), avatarFilePath);

        // 20240719创建likemusic.xml文件并添加根节点
        QString likemusicFilePath = musicPath + "/likemusic.xml";
        QFile likemusicFile(likemusicFilePath);
        if(likemusicFile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&likemusicFile);
            out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            out << "<MusicList>\n";
            out << "</MusicList>\n";
            likemusicFile.close();
            qDebug() << "likemusic.xml 文件创建成功: " << likemusicFilePath;
        }
        else
        {
            QMessageBox::warning(this, "警告", "likemusic.xml 文件创建失败" + likemusicFilePath);
            return;
        }

    }
    else if (response == "sign up failed: user already exists")
    {
        QMessageBox::warning(this, "警告", "注册失败: 用户已存在");
    }
    else if (response == "sign up failed due to database error")
    {
        QMessageBox::warning(this, "警告", "注册失败: 数据库错误");
    }
    else if (response == "sign up failed: directory creation failed")
    {
        QMessageBox::warning(this, "警告", "注册失败: 创建目录失败");
    }
}


void SignUp::backtomain()
{
    // 启用主界面控件----qobject_cast用于类型安全的强制转换
    if (auto widget = qobject_cast<Widget *>(parentWidget()))// parentWidget() 是 QWidget 类的一个方法，它返回当前窗口部件的父窗口部件的指针。如果没有父窗口部件，则返回 nullptr
    {
        widget->enableControls();
    }

    this->parentWidget()->show();   //调用parentWidget()返回上一界面的this指针，并显示
    delete this;      //关闭本窗口
}

