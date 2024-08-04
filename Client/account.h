#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QDomDocument>


namespace Ui {
class Account;
}

class Account : public QWidget
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr);
    ~Account();

    void SetParams(const QString& account, const QString& username, const QString& filepath);// 第三个是图片的路径

    QString GetAccount();


signals:


public:
    void deleteAccountXml();// 删除账户节点信息


public slots:


private:
    Ui::Account *ui;
    QDomDocument doc;
};

#endif // ACCOUNT_H
