#include "afterlogin.h"
#include "ui_afterlogin.h"
#include <QFileDialog>
#include <QPixmap>
#include <QPalette>
#include <QFile>
#include <QDomDocument>
#include <QMessageBox>
#include <QDebug>
#include "musicplayer.h"
#include "http.h"
#include "listwidget.h"



AfterLogin::AfterLogin(QWidget *parent, MyClientSocket *socket) :
    QWidget(parent),
    ui(new Ui::AfterLogin),
    CSocket(socket) // 初始化套接字指针
{
    ui->setupUi(this);

    // 连接返回登录按钮的点击信号到槽函数
    connect(ui->pushButton_back, &QPushButton::clicked, this, &AfterLogin::backclicked);
    // 更改头像
    connect(ui->pushButton_changeHeaderimage, &QPushButton::clicked, this, &AfterLogin::changeAvatar);
    // 接收数据时处理
    connect(CSocket, &MyClientSocket::DataRecv, this, &AfterLogin::headerimageDataRecv); // 连接信号到槽

    // 连接打开音乐播放器按钮的点击信号
    connect(ui->pushButton_enterMusicplayer, &QPushButton::clicked, this, &AfterLogin::openMusicPlayer);
    // 连接打开AI界面按钮的点击信号到槽函数
    connect(ui->pushButton_AIchat, &QPushButton::clicked, this, &AfterLogin::openHTTP);
    // 20240716在线音乐播放--在这里进行信号与槽的连接等操作
    connect(ui->pushButton_onlinemusic, &QPushButton::clicked, this, &AfterLogin::OnlineMusic);

}

AfterLogin::~AfterLogin()
{
    delete ui;
}

// 设置登录信息
void AfterLogin::setLoginInfo(const QString &username, const QString &nickname ,const QString &headerpath)
{
    ui->label_afterLoginName->setText(username);
    ui->label_nickname->setText(nickname);
    // 加载头像图片
    QPixmap originalPixmap(headerpath);

    // 定义目标尺寸
    QSize targetSize(100, 100); // 调整为你希望的尺寸
    // 缩放头像图片
    QPixmap scaledPixmap = originalPixmap.scaled(targetSize, Qt::KeepAspectRatio);
    // 设置缩放后的图片到label
    ui->label_afterLoginImage->setPixmap(scaledPixmap);

}

// 更新xml文件中的头像路径
void AfterLogin::updateAvatarPathInXml(const QString &username, const QString &newAvatarPath)
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

    // 更新对应账号的头像路径
    QDomElement root = doc.documentElement();
    QDomNodeList accounts = root.elementsByTagName("账号");
    for (int i = 0; i < accounts.size(); ++i)
    {
        QDomElement account = accounts.at(i).toElement();
        if (account.attribute("账号") == username)
        {
            account.setAttribute("头像", newAvatarPath);
            break;
        }
    }
    // 保存更新后的 XML 文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "无法打开 account.xml 文件进行写入";
        return;
    }
    QTextStream out(&file);
    doc.save(out, 4); // 缩进为4个空格
    file.close();
    qDebug() << "头像路径已更新到 account.xml 文件";
}

// 改变头像
void AfterLogin::changeAvatar()
{
    // 打开文件对话框选择新头像文件
    QString newImagePath = QFileDialog::getOpenFileName(this, tr("SelectHeaderImage"), QDir::homePath(), tr("图片文件 (*.png *.jpg *.jpeg)"));
    if (!newImagePath.isEmpty())
    {
        // 设置新的头像图片到界面
        // 加载头像图片
        QPixmap originalPixmap(newImagePath);
        // 定义目标尺寸
        QSize targetSize(100, 100); // 调整为你希望的尺寸
        // 缩放头像图片
        QPixmap scaledPixmap = originalPixmap.scaled(targetSize, Qt::KeepAspectRatio);
        ui->label_afterLoginImage->setPixmap(scaledPixmap);

        // 保存新头像路径到 XML 文件
        QString username = ui->label_afterLoginName->text();
        updateAvatarPathInXml(username, newImagePath);

        // 读取图片数据并进行Base64编码
        QFile file(newImagePath);
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "无法打开选中的头像文件";
            return;
        }
        QByteArray imageData = file.readAll();//整个文件内容到 imageData
        QString base64Data = imageData.toBase64();//toBase64() 方法将 imageData 转换为 Base64 编码的字符串
        // 获取图像文件名（不含路径部分）
        QString imageName = QFileInfo(newImagePath).fileName();

        // 构造JSON对象发送到服务器
        QJsonObject json;
        json["request"] = "UploadHeaderImage";
        json["username"] = username;
        json["image_data"] = QString(base64Data);
        json["image_file_name"] = imageName; // 添加图像文件名字段
        // json["total_size"] = base64Data.size();

        // 将 JSON 对象转换为 QByteArray
        QByteArray content = QJsonDocument(json).toJson();
        // 显示发送数据的大小
        qDebug()<< "Sending data size: " << content.size() << endl;
        size_t size = static_cast<size_t>(content.size());
        content.insert(0, reinterpret_cast<const char*>(&size), sizeof(size_t));
        CSocket->sendData(content);
        qDebug() << "更换的新头像上传成功";
    }
}

// 头像数据接收
void AfterLogin::headerimageDataRecv(QByteArray array)
{
    //---处理接受的数据
    QJsonDocument doc = QJsonDocument::fromJson(array);// 将一个JSON格式的字节数组(array)转换为一个QJsonDocument对象
    QJsonObject obj = doc.object();
    QString response = obj["response"].toString();
    if(response == "upload success")
    {
        QMessageBox::information(this, "上传成功", "头像上传成功");
    }
//    else
//    {
//        QMessageBox::warning(this, "上传失败", "头像上传失败");
//    }
}

// 进入本地和下载界面
void AfterLogin::openMusicPlayer()
{
    MusicPlayer *musicPlayer = new MusicPlayer(nullptr, CSocket);
    musicPlayer->show();
}

// 20240716--在线音乐界面
void AfterLogin::OnlineMusic()
{
    ListWidget *newlistWidget = new ListWidget(nullptr, CSocket); // 创建新界面实例，并传递套接字
    QString username = ui->label_afterLoginName->text(); // 获取用户名
    newlistWidget->setUsername(username); // 设置用户名
    newlistWidget->show();
    // this->hide(); // 可选：隐藏当前界面
}

// 进入AI界面
void AfterLogin::openHTTP()
{
    HTTP *httpWidget = new HTTP(nullptr, CSocket);
    httpWidget->show();
}

void AfterLogin::backclicked()
{
    this->hide();
}

