#include "http.h"
#include "ui_http.h"
#include <QNetworkRequest>       // HTTP请求类
#include <QNetworkAccessManager> // 应答处理类
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

struct HTTPPrivate
{
    QString access_tocken;// 权限证书
    QNetworkRequest request;// 请求对象
    QNetworkAccessManager manager;// 应答处理对象

    std::vector<QString> RoleChat;   //用户说的话
    std::vector<QString> AssiantChat;//
};

HTTP::HTTP(QWidget *parent, MyClientSocket *socket) :
    QWidget(parent),
    ui(new Ui::HTTP),p(new HTTPPrivate),CSocket(socket) // 初始化套接字指针
{
    ui->setupUi(this);
    InitAccessTocken();// 获取权限初始化
    connect(ui->pushButton, &QPushButton::clicked, this, &HTTP::ChatAI);

    connect(ui->pushButton_image, &QPushButton::clicked, this, &HTTP::ImageAI);


}

HTTP::~HTTP()
{
    delete ui;
}

// 获取权限
void HTTP::InitAccessTocken()
{
    p->request.setUrl(QUrl("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=YQ0BfGj0VagheWcYGcmVg8tF&client_secret=U6CZeATz5EZWiRS2rNT4nYXb243ljB3c"));// 设置路径
    p->request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");// 设置文本类型

    // 应答指针
    QNetworkReply *reply = p->manager.post(p->request,"");// 返回的应答
    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        // 应答没有错误
        if(reply->error() == QNetworkReply::NoError)
        {
            auto content = reply->readAll();
            auto obj = QJsonDocument::fromJson(content);
            p->access_tocken = obj["access_token"].toString();
            qDebug()<<p->access_tocken<<endl;
        }
        else
        {
            qDebug()<<reply->errorString()<<endl;//错误信息
        }
    });

}

// 对话AI
void HTTP::ChatAI()
{
    // Header参数上面已经设置过了
    // 再获得Query参数
    QString url = QString("https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions_pro?access_token=")
            + p->access_tocken;
    p->request.setUrl(QUrl(url));
    // p->request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // Body参数
    QJsonObject obj;
    QJsonArray array;

    // 多轮对话插入(添加历史对话)
    for (size_t i = 0; i < p->RoleChat.size(); i++)
    {
        QJsonObject user;
        user["role"] = "user";
        user["content"] = p->RoleChat[i];
        array.append(user);

        QJsonObject assiant;
        assiant["role"] = "assistant";
        assiant["content"] = p->AssiantChat[i];
        array.append(assiant);
    }

    QJsonObject chatObj;
    chatObj["role"] = "user";
    chatObj["content"] = ui->textEdit_send->toPlainText();// 获取文本
    p->RoleChat.push_back(ui->textEdit_send->toPlainText());
    array.append(chatObj);
    obj["messages"] = array;

    // 应答指针
    QNetworkReply *reply = p->manager.post(p->request,QJsonDocument(obj).toJson());// 用post方法取请求，返回值是*reply
    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        // 应答没有错误
        if(reply->error() == QNetworkReply::NoError)
        {

            auto content = reply->readAll();
            auto obj = QJsonDocument::fromJson(content);
            // qDebug()<<content <<endl;
            ui->textEdit_reply->setText(obj["result"].toString());

            p->AssiantChat.push_back(obj["result"].toString());
        }
        else
        {
            qDebug()<<reply->errorString()<<endl;//错误信息
        }
    });

}

// 生成图片
void HTTP::ImageAI()
{
    QString Url = QString("https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/text2image/sd_xl?access_token=")
            + p->access_tocken;
    p->request.setUrl(QUrl(Url));

    QJsonObject obj;

    obj["prompt"] = ui->textEdit_send->toPlainText();

    // 应答指针
    QNetworkReply *reply = p->manager.post(p->request,QJsonDocument(obj).toJson());// 用post方法取请求，返回值是*reply
    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        // 应答没有错误
        if(reply->error() == QNetworkReply::NoError)
        {

            auto content = reply->readAll();
            auto obj = QJsonDocument::fromJson(content);
            auto arr = obj["data"].toArray();
            if(arr.size() == 0)
            {
                qDebug()<< "获取图片失败\n";
            }
            else
            {
                // 获取Base64编码的图片数据并解码为QImage
                auto ImageData = QByteArray::fromBase64(arr[0].toObject()["b64_image"].toString().toUtf8());//转换
                QImage image;
                image.loadFromData(ImageData);

                ui->label_image->setPixmap(QPixmap::fromImage(image).scaled(ui->label_image->size()));
                QPixmap pixmap = QPixmap::fromImage(image);
                QPalette palette;
                palette.setBrush(this->backgroundRole(), QBrush(pixmap));
                this->setPalette(palette);

            }
        }
        else
        {
            qDebug()<<reply->errorString()<<endl;//错误信息
        }
    });

}



