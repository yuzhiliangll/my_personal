#include "account.h"
#include "ui_account.h"
#include <QPixmap>
#include <QFile>
#include <QDomDocument>
#include <QMessageBox>
#include <QDebug>



Account::Account(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);

    connect(ui->pushButton_DeleteAvatar, &QPushButton::clicked, this, &Account::deleteAccountXml);
}

Account::~Account()
{
    delete ui;
}

void Account::SetParams(const QString &account, const QString &username, const QString &filepath)
{
    // ui->label_Post->setFixedWidth(this->width() / 3);
    ui->label_Post->setFixedSize(70, 65);
    ui->label_account->setText(account);
    ui->label_username->setText(username);

    // 调整图片大小，使其比label_Post的尺寸略小
    int width = static_cast<int>(ui->label_Post->width() * 0.9);  // 调整宽度为label_Post宽度的90%
    int height = static_cast<int>(ui->label_Post->height() * 0.9); // 调整高度为label_Post高度的90%

    QPixmap m = QPixmap(filepath).scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);//将其按指定的尺寸进行缩放，确保图像不会变形
    ui->label_Post->setPixmap(m);

}

QString Account::GetAccount()
{
    return ui->label_account->text();
}

// 删除账户节点信息
void Account::deleteAccountXml()
{

    // XMl
    QFile file(R"(C:\Users\21196\Desktop\QTnote_lv\20140702_xml\account.xml)");
    if(file.open(QIODevice::ReadOnly) == false)
    {
        qDebug()<< "文件打开失败!\n";
    }
    auto Content = file.readAll();
    file.close();// 读完后关闭

    QString errorMsg;// 错误信息
    int line,column;

    QDomDocument doc1;
    if (doc1.setContent(Content, &errorMsg, &line, &column) == false)
    {
        qDebug() << "line : " << line << "column : " << column << "errormsg: " << errorMsg << endl;
        return;
    }

    qDebug()<< "xml解析成功!\n";

    QDomElement root = doc1.documentElement();
    QDomNodeList accounts = root.elementsByTagName("账号");// 获得所有标签名为 账号 的节点

    QString targetAccount = GetAccount();

    for (int i = 0; i < accounts.size(); ++i)
    {
        QDomNode accountNode = accounts.at(i);
        QDomElement accountElement = accountNode.toElement();
        if (accountElement.attribute("账号") == targetAccount)
        {
            root.removeChild(accountNode);
            qDebug() << "已删除账户: " << targetAccount;
            break;
        }
    }

    // 保存修改后的XML内容
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "无法打开文件进行写入!";
        return;
    }

    QTextStream outStream(&file);
    doc1.save(outStream, 4);
    file.close();

    QMessageBox::information(this, "提示", "该账户本地登录信息已删除");
}
