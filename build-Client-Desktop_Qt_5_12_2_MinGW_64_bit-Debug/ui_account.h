/********************************************************************************
** Form generated from reading UI file 'account.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNT_H
#define UI_ACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Account
{
public:
    QLabel *label_Post;
    QLabel *label_username;
    QLabel *label_account;
    QPushButton *pushButton_DeleteAvatar;

    void setupUi(QWidget *Account)
    {
        if (Account->objectName().isEmpty())
            Account->setObjectName(QString::fromUtf8("Account"));
        Account->resize(369, 139);
        label_Post = new QLabel(Account);
        label_Post->setObjectName(QString::fromUtf8("label_Post"));
        label_Post->setGeometry(QRect(10, 28, 81, 61));
        label_username = new QLabel(Account);
        label_username->setObjectName(QString::fromUtf8("label_username"));
        label_username->setGeometry(QRect(110, 30, 201, 21));
        label_account = new QLabel(Account);
        label_account->setObjectName(QString::fromUtf8("label_account"));
        label_account->setGeometry(QRect(110, 70, 201, 21));
        pushButton_DeleteAvatar = new QPushButton(Account);
        pushButton_DeleteAvatar->setObjectName(QString::fromUtf8("pushButton_DeleteAvatar"));
        pushButton_DeleteAvatar->setGeometry(QRect(320, 50, 30, 30));
        pushButton_DeleteAvatar->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_DeleteAvatar {\n"
"	\n"
"	image: url(:/images/deleteAvatar.png);\n"
"    border: 1px solid gray;\n"
"    border: none; /* \345\216\273\346\216\211\350\276\271\346\241\206 */\n"
"    border-radius: 15px; /* \350\256\276\347\275\256\344\270\272\345\215\212\345\276\204\347\232\204\344\270\200\345\215\212 */\n"
"    min-width: 30px;  /* \350\256\276\347\275\256\346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 30px; /* \350\256\276\347\275\256\346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"    max-width: 30px;  /* \350\256\276\347\275\256\346\234\200\345\244\247\345\256\275\345\272\246 */\n"
"    max-height: 30px; /* \350\256\276\347\275\256\346\234\200\345\244\247\351\253\230\345\272\246 */\n"
"    text-align: center; /* \344\275\277\346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"}\n"
"QPushButton#pushButton_DeleteAvatar:hover {\n"
"    background-color: lightgreen; /* \346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\350\211\262\345\217\230\344"
                        "\270\272\346\265\205\347\273\277\350\211\262 */\n"
"}\n"
"QPushButton#pushButton_DeleteAvatar:pressed {\n"
"    background-color: red; /* Background color when pressed */\n"
"}"));

        retranslateUi(Account);

        QMetaObject::connectSlotsByName(Account);
    } // setupUi

    void retranslateUi(QWidget *Account)
    {
        Account->setWindowTitle(QApplication::translate("Account", "Form", nullptr));
        label_Post->setText(QApplication::translate("Account", "\345\244\264\345\203\217", nullptr));
        label_username->setText(QApplication::translate("Account", "\345\220\215\347\247\260", nullptr));
        label_account->setText(QApplication::translate("Account", "\350\264\246\345\217\267", nullptr));
        pushButton_DeleteAvatar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Account: public Ui_Account {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNT_H
