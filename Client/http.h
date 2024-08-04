#ifndef HTTP_H
#define HTTP_H

#include <QWidget>
#include "myclientsocket.h"
#include <QFileDialog>
#include <QPixmap>
#include <QPalette>

namespace Ui {
class HTTP;
}

struct HTTPPrivate;

class HTTP : public QWidget
{
    Q_OBJECT

public:
    explicit HTTP(QWidget *parent = nullptr, MyClientSocket *socket = nullptr); // 构造函数声明
    ~HTTP();

    // 获取权限
    void InitAccessTocken();

signals:


public slots:// 槽函数
    // 对话AI
    void ChatAI();

    void ImageAI();// 生成图片


private:
    Ui::HTTP *ui;
    HTTPPrivate *p;
    MyClientSocket *CSocket; // 套接字指针

    QString username;  //20240723__ 保存用户名
};

#endif // HTTP_H
