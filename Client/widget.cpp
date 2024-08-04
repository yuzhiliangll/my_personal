#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include "myclientsocket.h"
#include "account.h"
#include <QFile>
#include <QDebug>
#include <QDomDocument>
#include <QFileDialog>// 文件对话框




Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    isPasswordVisible(false), // 初始状态密码为不可见
    c(new MyClientSocket(this)), // ----初始化 MyClientSocket
    netconwidget(nullptr), // 初始化 netconwidget 为 nullptr
    afterwidget(nullptr) // 初始化 AfterLogin 窗口指针
{
    ui->setupUi(this);
    w = new QListWidget(this);// 20240702--当前窗体作为我的父窗体
    w->hide();//先隐藏掉--不然会一起显示
    w->setFixedWidth(ui->lineEdit_username->width());
    w->setFixedHeight(200);// 拉高

    // c = new MyClientSocket(this);// 加this ,将当前对象作为父对象，该对象释放时会自动释放子对象

    // c->Connect("192.168.192.128", 8081);// 连接主机IP---初始连接
    QPixmap headerIcon(":/images/header_image.png");
    ui->pushButton_headerimage->setIcon(headerIcon);
    ui->pushButton_headerimage->setIconSize(QSize(50, 50)); // 设置图标大小为64x64像素

    initializeAccountMap();


    // 20240702--待实现登录后的账号通过xml保存在本地
    connect(ui->lineEdit_username, &QLineEdit::textChanged, [this]()//在每次输入框文本发生变化时被调用
    {
        QString searchText = ui->lineEdit_username->text().trimmed(); // 获取输入文本并去除首尾空格
        if (searchText.isEmpty())
        {
            w->hide();
            return;
        }
        int count = 0;// 清空标志位
        w->clear();// 清空列表
        for(auto value : AccountMap)// 遍历每一对键值对
        {
            if (value.first.contains(ui->lineEdit_username->text()))// 如果包含文本，添加到列表
            {
                count++;
                Account * a = new Account;
                auto Node = value.second.toElement();// 将节点（value.second）转换为 QDomElement 类型。QDomElement 是 QDomNode 的子类
                a->SetParams(Node.attribute("账号"), Node.attribute("用户名"), Node.attribute("头像"));
                QListWidgetItem *item = new QListWidgetItem;// 创建新的列表项
                item->setSizeHint(a->size());
                w->addItem(item);// 先添加列表项
                // 然后把小界面塞到listwidget里面
                w->setItemWidget(item, a);
            }
        }
        /*20240708*/
        // 设置小界面位置和显示--合适
        w->move(ui->lineEdit_username->x(), ui->lineEdit_username->y() + ui->lineEdit_username->height());
        if(searchText.isEmpty() || count == 0)
        {
            w->hide();
        }
        else
        {
            w->show();
        }
    });


    // 20240707--连接记住密码的 checkbox 的状态改变信号
    connect(ui->checkBox_rememberPasswd, &QCheckBox::stateChanged, this, &Widget::rememberPasswordChanged);


    // 点击界面里的账号 补全到输入框中
    connect(w, &QListWidget::clicked, [this]()
    {
        Account *a = dynamic_cast<Account*>(w->itemWidget(w->currentItem()));// 用于父子之间转换--尝试将当前点击的条目的部件转换为 Account 类型，以便获取账号信息
        ui->lineEdit_username->setText(a->GetAccount());// 将获取到的账号信息设置到用户输入框中
        // 检查XML中的记住密码标志位
        bool rememberPassword = readRememberPasswordFromXml(a->GetAccount());
        ui->checkBox_rememberPasswd->setChecked(rememberPassword);
        if (rememberPassword)
        {
            ui->lineEdit_passwd->setText("········"); // 如果记住密码，显示"········"
        }
        else
        {
            ui->lineEdit_passwd->clear(); // 否则清空密码输入框
        }
        w->hide();// 完成后隐藏
    });



    // Lambda表达式绑定
    // 连接成功时显示提示信息
    connect(c, &MyClientSocket::Connected, [this]()
    {
        // information 蓝色对话框 warning 黄色警告
        QMessageBox::information(this, "提示", "连接成功!");
        netconwidget->close();
    });

    // 断开连接时显示警告信息
    connect(c, &MyClientSocket::Disconnected, [this]()
    {
        QMessageBox::warning(this, "警告", "断开连接!");
    });

    // 连接网络配置按钮的点击信号到  pushButton_NetCon槽函数
    connect(ui->NetworkConfiguration, &QPushButton::clicked, this, &Widget::pushButton_NetCon);



    // 有一个 QPushButton 用于切换密码显示状态
    // 设置密码输入框初始状态为隐藏
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);
    ui->pushButton_unseen->setIcon(QIcon(":/images/Unseen.png"));// 隐藏
    connect(ui->pushButton_unseen, &QPushButton::clicked, this, &Widget::PasswordStatusFlipped);

    // 登录按钮点击事件
    connect(ui->pushButton_Login, &QPushButton::clicked, this, &Widget::Login);

    // 注册按钮点击事件
    connect(ui->pushButton_SignUp, &QPushButton::clicked, this, &Widget::pushButton_SignUp);

    // 接收数据时处理
    connect(c, &MyClientSocket::DataRecv, this, &Widget::handleDataRecv); // 连接信号到槽



}

// 20240702--方法来获取 MyClientSocket 实例的指针 (好像用不到,直接把套接字传给另一个SignUp实例)
MyClientSocket *Widget::getClientSocket() const
{
    return c;
}

Widget::~Widget()
{
    delete ui;
    delete netconwidget;
    delete w; // 添加释放 QListWidget 的语句
    delete afterwidget; // 释放 AfterLogin 窗口指针
}

// 登录处理
void Widget::Login()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();

    // 简单的前端验证
    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请填写完整信息！");
        return;
    }

    // 构建登录请求的 JSON 数据
    QJsonObject jsonObj;
    jsonObj["request"] = "Login";
    jsonObj["username"] = username;
    jsonObj["passwd"] = password;
    jsonObj["rememberPassword"] = ui->checkBox_rememberPasswd->isChecked() ? "true" : "false";; // 20240707_接收字符串true 或 false 作为记住密码的标志位

    // --------正文主体
    // 将 JSON 对象转换为 QByteArray
    QByteArray content = QJsonDocument(jsonObj).toJson();
    size_t size = static_cast<size_t>(content.size());
    content.insert(0, reinterpret_cast<const char*>(&size), sizeof(size_t));

    // -----使用 MyClientSocket 发送登录请求
    c->sendData(content); // 这里假设 MyClientSocket 中有一个 sendData 方法用于发送数据
    qDebug()<< content << endl;

}

// 初始化登陆列表项
void Widget::initializeAccountMap()
{
    /* xml  */
    QFile file(R"(C:\Users\21196\Desktop\QTnote_lv\20140702_xml\account.xml)");// 字面量
    if(file.open(QIODevice::ReadOnly) == false)
    {
        qDebug()<< "文件打开失败!\n";
    }
    auto Content = file.readAll();
    file.close();// 读完后关闭

    QString errorMsg; // 错误信息
    int line,column; // 行 列
    if(doc.setContent(Content, &errorMsg, &line, &column) == false)
    {
        qDebug() << "line : "<< line << "column : " << column << "errormsg : " << errorMsg << endl;
        return;
    }
    qDebug()<<"xml解析成功!\n";

    auto root = doc.documentElement();
    for(auto Node = root.firstChild(); !Node.isNull(); Node = Node.nextSibling())
    {
        AccountMap[Node.toElement().attribute("账号")] = Node;// 把账号里的东西存进去
    }
}

// 20240707--添加新的槽函数 rememberPasswordChanged 处理记住密码复选框状态变化
void Widget::rememberPasswordChanged(int state)
{
    rememberPassword = (state == Qt::Checked);
}

// 添加账号信息到account.xml中
void  Widget::addAccountIntoXml(const QString &filePath, const QString &account, const QString &username, const QString &avatarPath, bool rememberPassword)
{
    QDomDocument doc1;
    QFile file(filePath);// 文件路径--- 字面量
    if(file.open(QIODevice::ReadOnly) == false)
    {
        qDebug()<< "文件打开失败!\n";
    }
    auto Content = file.readAll();
    file.close();// 读完后关闭

    QString errorMsg; // 错误信息
    int line,column; // 行 列
    if(doc1.setContent(Content, &errorMsg, &line, &column) == false)
    {
        qDebug() << "line : "<< line << "column : " << column << "errormsg : " << errorMsg << endl;
        return;
    }
    qDebug()<<"xml解析成功!\n";
    // 获取根元素
    QDomElement root = doc1.documentElement();//返回 XML 文档的根元素

    // 先判断是否已经存在相同账号的元素,第二判断记住密码标志位是否要更新
    QDomNodeList accounts = root.elementsByTagName("账号");// 返回文档中所有与指定标签名匹配的元素
    for (int i = 0; i < accounts.count(); ++i)// 遍历 accounts 中的每一个元素
    {
        QDomElement existingAccount = accounts.at(i).toElement();//返回当前索引 i 处的节点，使用 .toElement() 将其转换为 QDomElement 类型 existingAccount
        if (existingAccount.attribute("账号") == account)//获取 existingAccount 元素的 "账号" 属性的值
        {
            qDebug()<< "Account already exists. Updating rememberPassword flag.";
            existingAccount.setAttribute("记住密码", rememberPassword ? "true" : "false");
            QFile outFile(filePath);
            if (outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                QTextStream stream(&outFile);
                doc1.save(stream, 4); // 缩进为4个空格
                outFile.close();
            }
            return;
        }
    }

    // 创建新的账号元素
    QDomElement accountElement = doc1.createElement("账号");
    accountElement.setAttribute("账号", account);
    accountElement.setAttribute("用户名", username);
    accountElement.setAttribute("头像", avatarPath);
    // 20240707--创建新的账号元素，并添加 rememberPassword 属性
    accountElement.setAttribute("记住密码", rememberPassword ? "true" : "false");// 使用0或1作为记住密码的标志位

    // 将账号元素添加到根元素中
    root.appendChild(accountElement);

    // 保存 XML 文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "无法打开 XML 文件进行写入！\n";
        return;
    }
    QTextStream out(&file);
    doc1.save(out, 4);// 缩进为4个空格
    file.close();
    qDebug() << "账号信息已成功添加到 XML 文件！\n";
}

// 20240707--从 XML 文件中读取记住密码标志位的函数
bool Widget::readRememberPasswordFromXml(const QString &username)
{
    QFile file(xmlFilePath);// 替换为实际的路径
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "无法打开 XML 文件进行读取！";
        return false;
    }
    QDomDocument doc1;
    auto content = file.readAll();
    file.close();

    QString errorMsg;
    int line, column;
    if (doc1.setContent(content, &errorMsg, &line, &column) == false)
    {
        qDebug() << "line : " << line << "column : " << column << "errormsg : " << errorMsg << endl;
        return false;
    }
    //qDebug() << "xml解析成功!\n";

    QDomElement root = doc.documentElement();
    QDomNodeList accounts = root.elementsByTagName("账号");
    for (int i = 0; i < accounts.count(); ++i)
    {
        QDomElement accountElement = accounts.at(i).toElement();
        if (accountElement.attribute("账号") == username)
        {
            return accountElement.attribute("记住密码") == "true";
        }
    }

    return false;
}

void Widget::handleDataRecv(QByteArray array)// -----
{
    //-------处理接受的数据
    QJsonDocument doc = QJsonDocument::fromJson(array);// 将一个JSON格式的字节数组（array）转换为一个QJsonDocument对象
    QJsonObject obj = doc.object();
    QString response = obj["response"].toString();
    QString username = ui->lineEdit_username->text(); // 获取用户名
    QString avatarPath = ""; // 根据需要，获取头像路径，可以是一个固定值或从其他地方获取

    if (response == "login success" || response == "login success remember password")
    {
        QMessageBox::information(this, "提示", "登录成功!");
        currentUsername = ui->lineEdit_username->text();// 从响应中获取用户名
        currentNickname = readNickname(currentUsername);// 获取用户昵称
        currentAvatarPath = readAvatarPath(currentUsername);// 从 XML 文件中获取当前头像路径

        // 检查是否有头像路径
        if (currentAvatarPath.isEmpty())
        {
            currentAvatarPath = headerimagepath; // 使用默认头像路径
        }
        // 保存账号信息到 XML 文件
        addAccountIntoXml(xmlFilePath, ui->lineEdit_username->text(), currentNickname, currentAvatarPath, rememberPassword);

        openAfterLoginWindow(); // 登录成功后打开 AfterLogin 界面

    }
    else if (response == "login failed: username or password incorrect")
    {
        QMessageBox::warning(this, "警告", "登录失败：用户名或密码错误");
    }
    else if (response == "login failed: user does not exist")
    {
        QMessageBox::warning(this, "警告", "登录失败：用户不存在");
    }


//    // 音乐文件下载
//    auto rootObj = QJsonDocument::fromJson(array).object();
//    auto Name = rootObj["FileName"].toString();// 获取文件名
//    qDebug() << Name << endl;

//    if (rootObj["request"].toString() == "DownLoadMusic")
//    {
//        auto Name = rootObj["FileName"].toString();// 获取文件名
//        QFile file("./" + Name);// 创建文件
//        qDebug() << "fileName: " << file.fileName() << endl;

//        file.open(QIODevice::Append);// 打开
//        file.write(QByteArray::fromHex(rootObj["data"].toString().toUtf8()));//  写入的文件转utf8编码
//        qDebug()<<rootObj["ReadSize"]<< endl;
//        file.close();
//    }

}

// 密码显示状态
void Widget::PasswordStatusFlipped()
{
    if(isPasswordVisible)
    {
        ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);
        ui->pushButton_unseen->setIcon(QIcon(":/images/Unseen.png"));// 隐藏密码
    }
    else
    {
        ui->lineEdit_passwd->setEchoMode(QLineEdit::Normal);
        ui->pushButton_unseen->setIcon(QIcon(":/images/Seen.png"));// 显示
    }
    isPasswordVisible = !isPasswordVisible; // 切换状态
}

// 创建 SignUp 实例时并且传递 MyClientSocket 指针---确保登陆与注册是同一个套接字
void Widget::pushButton_SignUp()
{
    // 禁用桌面控件
    disableControls();

    // 传递主界面的this指针给跳转界面，否则子界面无法调用parentWidget()
    // 并且再加一个参数传递 MyClientSocket 指针 以避免Socket is not connected错误
    SignUp *SignUpWidget = new SignUp(this, c);// 创建了一个新的SignUp类的实例（通常是一个新的窗口或对话框），并将当前Widget实例（通过this指针）作为其父对象传递给它
    // 监视SignUpWidget的destroyed信号，并调用一个Lambda表达式重新启用主窗口控件
    SignUpWidget->show();    //显示子界面
    // this->hide();   // 隐藏了当前的Widget窗口
}

// 网络配置界面跳转
void Widget::pushButton_NetCon()
{
    if (!netconwidget)
    {
        netconwidget = new NetCon(nullptr, c); // 创建网络配置界面对象，如果尚未创建
        connect(netconwidget, &NetCon::connectionInfoChanged, this, &Widget::updateConnectionInfo); // 使用新的配置信号
    }
    netconwidget->show(); // 显示网络配置界面
    // this->hide();
}

// 更新连接配置信息
void Widget::updateConnectionInfo(const QString &ip, int port)
{
    QMessageBox::information(this, "提示", "连接配置已更新！");
    c->Connect(ip, port); // 使用新的IP和端口连接
}

// 打开登录之后的新窗口
void Widget::openAfterLoginWindow()
{
    if(!afterwidget)
    {
        afterwidget = new AfterLogin(nullptr, c);// 创建 AfterLogin 界面，并传递套接字指针
    }
    afterwidget->setLoginInfo(currentUsername,  currentNickname, currentAvatarPath);// 设置登录信息
    afterwidget->show();
    this->close();
    //this->hide();
}

// 添加读取用户昵称的函数
QString Widget::readNickname(const QString &username)
{
    QFile file(R"(C:\Users\21196\Desktop\QTnote_lv\20140702_xml\SignUpInfo.xml)");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "警告", "无法打开 account.xml 文件");
        return QString();
    }

    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        QMessageBox::warning(this, "警告", "无法解析 account.xml 文件");
        return QString();
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList accounts = root.elementsByTagName("账号");

    for (int i = 0; i < accounts.size(); ++i)
    {
        QDomElement account = accounts.at(i).toElement();
        if (account.attribute("账号") == username)
        {
            return account.attribute("用户名");
        }
    }
    return QString(); // 如果没有找到对应的用户，返回空字符串
}

// 添加读取头像路径的函数声明
QString Widget::readAvatarPath(const QString &username)
{
    QFile file(xmlFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "警告", "无法打开 account.xml 文件");
        return QString();
    }

    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        QMessageBox::warning(this, "警告", "无法解析 account.xml 文件");
        return QString();
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList accounts = root.elementsByTagName("账号");

    for (int i = 0; i < accounts.size(); ++i)
    {
        QDomElement account = accounts.at(i).toElement();
        if (account.attribute("账号") == username)
        {
            return account.attribute("头像");
        }
    }
    return QString(); // 如果没有找到对应的用户，返回空字符串
}


// 发送音乐下载请求
//void Widget::DownLoadMusic(QByteArray info)
//void Widget::DownLoadMusic()
//{

//    // 构建下载请求的 JSON 数据
//    QJsonObject jsonObj;
//    jsonObj["request"] = "DownLoadMusic";
//    jsonObj["MusicName"] = "music";

//    // 将 JSON 对象转换为 QByteArray
//    QByteArray content = QJsonDocument(jsonObj).toJson();
//    size_t size = static_cast<size_t>(content.size());
//    content.insert(0, reinterpret_cast<const char*>(&size), sizeof(size_t));

//    // -----使用 MyClientSocket 发送登录请求
//    c->sendData(content); // 这里假设 MyClientSocket 中有一个 sendData 方法用于发送数据
//    qDebug()<< content << endl;
//}
// 进入注册页面: 控件失效
void Widget::disableControls()
{
    ui->lineEdit_username->setEnabled(false);
    ui->lineEdit_passwd->setEnabled(false);
    ui->pushButton_Login->setEnabled(false);
    ui->pushButton_SignUp->setEnabled(false);
    ui->NetworkConfiguration->setEnabled(false);

}

void Widget::enableControls()
{
    ui->lineEdit_username->setEnabled(true);
    ui->lineEdit_passwd->setEnabled(true);
    ui->pushButton_Login->setEnabled(true);
    ui->pushButton_SignUp->setEnabled(true);
    ui->NetworkConfiguration->setEnabled(true);
}
