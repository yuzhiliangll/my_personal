/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton_Login;
    QLineEdit *lineEdit_username;
    QLineEdit *lineEdit_passwd;
    QPushButton *pushButton_SignUp;
    QLabel *label_up;
    QLabel *label_account;
    QLabel *label_password;
    QPushButton *pushButton_unseen;
    QCheckBox *checkBox_rememberPasswd;
    QPushButton *NetworkConfiguration;
    QPushButton *pushButton_headerimage;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(527, 361);
        Widget->setStyleSheet(QString::fromUtf8("QWidget#label_up\n"
"{\n"
"background-color: rgb(85, 255, 255);\n"
"}\n"
"QWidget{\n"
"background-color: rgb(255, 255, 255);\n"
"}"));
        pushButton_Login = new QPushButton(Widget);
        pushButton_Login->setObjectName(QString::fromUtf8("pushButton_Login"));
        pushButton_Login->setGeometry(QRect(140, 310, 71, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        pushButton_Login->setFont(font);
        pushButton_Login->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_Login{\n"
"background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0, \n"
"stop:0.0112994 rgba(210, 188, 235, 255), \n"
"stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(50, 50, 50);\n"
" \n"
"border:0px groove gray;border-radius:7px;\n"
"padding:2px 4px;\n"
"font: 14pt \"\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)\";\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton#pushButton_Login:hover {\n"
"    background-color: lightgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250hover\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"QPushButton#pushButton_Login:pressed {\n"
"    background-color: darkgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250pressed\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}"));
        lineEdit_username = new QLineEdit(Widget);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));
        lineEdit_username->setGeometry(QRect(110, 130, 351, 41));
        lineEdit_passwd = new QLineEdit(Widget);
        lineEdit_passwd->setObjectName(QString::fromUtf8("lineEdit_passwd"));
        lineEdit_passwd->setGeometry(QRect(110, 230, 351, 41));
        pushButton_SignUp = new QPushButton(Widget);
        pushButton_SignUp->setObjectName(QString::fromUtf8("pushButton_SignUp"));
        pushButton_SignUp->setGeometry(QRect(360, 310, 71, 31));
        pushButton_SignUp->setFont(font);
        pushButton_SignUp->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_SignUp {\n"
"    background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0, \n"
"stop:0.0112994 rgba(210, 188, 235, 255), \n"
"stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(50, 50, 50);\n"
" \n"
"border:0px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 14pt \"\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)\";\n"
"}\n"
"\n"
"QPushButton#pushButton_SignUp:hover {\n"
"    background-color: lightgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250pressed\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"QPushButton#pushButton_SignUp:pressed {\n"
"    background-color: darkgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250pressed\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}"));
        label_up = new QLabel(Widget);
        label_up->setObjectName(QString::fromUtf8("label_up"));
        label_up->setGeometry(QRect(0, -1, 531, 121));
        label_up->setStyleSheet(QString::fromUtf8(""));
        label_account = new QLabel(Widget);
        label_account->setObjectName(QString::fromUtf8("label_account"));
        label_account->setGeometry(QRect(60, 130, 32, 32));
        label_account->setStyleSheet(QString::fromUtf8("QLabel#label_account {\n"
"	\n"
"	image: url(:/images/Line_Account.png);\n"
"    border: 1px solid gray;\n"
"    border-radius: 15px; /* \350\256\276\347\275\256\344\270\272\345\215\212\345\276\204\347\232\204\344\270\200\345\215\212 */\n"
"    min-width: 30px;  /* \350\256\276\347\275\256\346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 30px; /* \350\256\276\347\275\256\346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"    max-width: 30px;  /* \350\256\276\347\275\256\346\234\200\345\244\247\345\256\275\345\272\246 */\n"
"    max-height: 30px; /* \350\256\276\347\275\256\346\234\200\345\244\247\351\253\230\345\272\246 */\n"
"    text-align: center; /* \344\275\277\346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"}"));
        label_password = new QLabel(Widget);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(60, 230, 32, 32));
        label_password->setStyleSheet(QString::fromUtf8("QLabel#label_password {\n"
"	\n"
"	image: url(:/images/Line_Password.png);\n"
"    border: 1px solid gray;\n"
"    border-radius: 15px; /* \350\256\276\347\275\256\344\270\272\345\215\212\345\276\204\347\232\204\344\270\200\345\215\212 */\n"
"    min-width: 30px;  /* \350\256\276\347\275\256\346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 30px; /* \350\256\276\347\275\256\346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"    max-width: 30px;  /* \350\256\276\347\275\256\346\234\200\345\244\247\345\256\275\345\272\246 */\n"
"    max-height: 30px; /* \350\256\276\347\275\256\346\234\200\345\244\247\351\253\230\345\272\246 */\n"
"    text-align: center; /* \344\275\277\346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"}"));
        pushButton_unseen = new QPushButton(Widget);
        pushButton_unseen->setObjectName(QString::fromUtf8("pushButton_unseen"));
        pushButton_unseen->setGeometry(QRect(470, 230, 30, 30));
        pushButton_unseen->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_unseen {\n"
"\n"
"    border: 1px solid gray;\n"
"    background-color: rgba(0, 0, 0, 0); /* \345\256\214\345\205\250\351\200\217\346\230\216 */\n"
"    border: none; /* \345\216\273\346\216\211\350\276\271\346\241\206 */\n"
"    border-radius: 15px; /* \350\256\276\347\275\256\344\270\272\345\215\212\345\276\204\347\232\204\344\270\200\345\215\212 */\n"
"    min-width: 30px;  /* \350\256\276\347\275\256\346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 30px; /* \350\256\276\347\275\256\346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"    max-width: 30px;  /* \350\256\276\347\275\256\346\234\200\345\244\247\345\256\275\345\272\246 */\n"
"    max-height: 30px; /* \350\256\276\347\275\256\346\234\200\345\244\247\351\253\230\345\272\246 */\n"
"    text-align: center; /* \344\275\277\346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"}\n"
"\n"
""));
        checkBox_rememberPasswd = new QCheckBox(Widget);
        checkBox_rememberPasswd->setObjectName(QString::fromUtf8("checkBox_rememberPasswd"));
        checkBox_rememberPasswd->setGeometry(QRect(220, 280, 111, 31));
        NetworkConfiguration = new QPushButton(Widget);
        NetworkConfiguration->setObjectName(QString::fromUtf8("NetworkConfiguration"));
        NetworkConfiguration->setGeometry(QRect(250, 310, 71, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)"));
        font1.setPointSize(7);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        NetworkConfiguration->setFont(font1);
        NetworkConfiguration->setStyleSheet(QString::fromUtf8("QPushButton#NetworkConfiguration{\n"
"background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0, \n"
"stop:0.0112994 rgba(210, 188, 235, 255), \n"
"stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(50, 50, 50);\n"
" \n"
"border:0px groove gray;border-radius:7px;\n"
"padding:2px 4px;\n"
"font: 7pt \"\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)\";\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton#NetworkConfiguration:hover {\n"
"    background-color: lightgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250hover\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"QPushButton#NetworkConfiguration:pressed {\n"
"    background-color: darkgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250pressed\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}"));
        pushButton_headerimage = new QPushButton(Widget);
        pushButton_headerimage->setObjectName(QString::fromUtf8("pushButton_headerimage"));
        pushButton_headerimage->setGeometry(QRect(240, 70, 52, 52));
        pushButton_headerimage->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_headerimage {\n"
"    border: 1px solid gray;\n"
"    border-radius: 25px; /* \344\275\277 QLabel \345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    min-width: 50px;  /* \350\256\276\347\275\256\346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 50px; /* \350\256\276\347\275\256\346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"    max-width: 50px;  /* \350\256\276\347\275\256\346\234\200\345\244\247\345\256\275\345\272\246 */\n"
"    max-height: 50px; /* \350\256\276\347\275\256\346\234\200\345\244\247\351\253\230\345\272\246 */\n"
"    text-align: center; /* \344\275\277\346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"}"));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton_Login->setText(QApplication::translate("Widget", "\347\231\273\345\275\225", nullptr));
        lineEdit_username->setPlaceholderText(QApplication::translate("Widget", "\350\264\246\346\210\267", nullptr));
        lineEdit_passwd->setPlaceholderText(QApplication::translate("Widget", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        pushButton_SignUp->setText(QApplication::translate("Widget", "\346\263\250\345\206\214", nullptr));
        label_up->setText(QString());
        label_account->setText(QString());
        label_password->setText(QString());
        pushButton_unseen->setText(QString());
        checkBox_rememberPasswd->setText(QApplication::translate("Widget", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        NetworkConfiguration->setText(QApplication::translate("Widget", "\347\275\221\347\273\234\351\205\215\347\275\256", nullptr));
        pushButton_headerimage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
