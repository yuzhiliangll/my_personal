/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QWidget *centralwidget;
    QLabel *label_accountSignUp;
    QLabel *label_account1;
    QLineEdit *lineEdit_account1;
    QLabel *label_passwd1;
    QLineEdit *lineEdit_passwd1;
    QLineEdit *lineEdit_passwd2;
    QPushButton *pushButton_unseenSignUp_1;
    QPushButton *pushButton_unseenSignUp_2;
    QLabel *label_passwd2;
    QPushButton *pushButton_signupfinal;
    QPushButton *backtomain;
    QCheckBox *checkBox_indicator;
    QLabel *label_readme;
    QLabel *label_signup_right;
    QLabel *label;
    QLineEdit *lineEdit_nickname;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName(QString::fromUtf8("SignUp"));
        SignUp->resize(611, 431);
        SignUp->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(SignUp);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_accountSignUp = new QLabel(centralwidget);
        label_accountSignUp->setObjectName(QString::fromUtf8("label_accountSignUp"));
        label_accountSignUp->setGeometry(QRect(20, 10, 346, 51));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_accountSignUp->setFont(font);
        label_accountSignUp->setAlignment(Qt::AlignCenter);
        label_account1 = new QLabel(centralwidget);
        label_account1->setObjectName(QString::fromUtf8("label_account1"));
        label_account1->setGeometry(QRect(20, 130, 100, 30));
        label_account1->setMinimumSize(QSize(100, 0));
        label_account1->setMaximumSize(QSize(100, 16777215));
        lineEdit_account1 = new QLineEdit(centralwidget);
        lineEdit_account1->setObjectName(QString::fromUtf8("lineEdit_account1"));
        lineEdit_account1->setGeometry(QRect(160, 130, 171, 31));
        lineEdit_account1->setMinimumSize(QSize(0, 30));
        lineEdit_account1->setStyleSheet(QString::fromUtf8("QLineEdit#lineEdit_account1 \n"
"{border-radius:14px;\n"
"					padding: 2 30 2 10;\n"
"        			border-width: 1px;\n"
"        			border-style: solid;\n"
"       				border-color: black;\n"
"}"));
        lineEdit_account1->setMaxLength(30);
        label_passwd1 = new QLabel(centralwidget);
        label_passwd1->setObjectName(QString::fromUtf8("label_passwd1"));
        label_passwd1->setGeometry(QRect(20, 170, 100, 30));
        label_passwd1->setMinimumSize(QSize(100, 0));
        label_passwd1->setMaximumSize(QSize(100, 16777215));
        lineEdit_passwd1 = new QLineEdit(centralwidget);
        lineEdit_passwd1->setObjectName(QString::fromUtf8("lineEdit_passwd1"));
        lineEdit_passwd1->setGeometry(QRect(160, 180, 171, 30));
        lineEdit_passwd1->setMinimumSize(QSize(0, 30));
        lineEdit_passwd1->setStyleSheet(QString::fromUtf8("QLineEdit#lineEdit_passwd1\n"
" {border-radius:14px;\n"
"					padding: 2 10 2 16;\n"
"        			border-width: 1px;\n"
"        			border-style: solid;\n"
"       				border-color: black;\n"
"}"));
        lineEdit_passwd1->setMaxLength(30);
        lineEdit_passwd1->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        lineEdit_passwd2 = new QLineEdit(centralwidget);
        lineEdit_passwd2->setObjectName(QString::fromUtf8("lineEdit_passwd2"));
        lineEdit_passwd2->setGeometry(QRect(160, 230, 171, 31));
        lineEdit_passwd2->setMinimumSize(QSize(0, 30));
        lineEdit_passwd2->setStyleSheet(QString::fromUtf8("QLineEdit#lineEdit_passwd2\n"
" {border-radius:14px;\n"
"					padding: 2 30 2 10;\n"
"        			border-width: 1px;\n"
"        			border-style: solid;\n"
"       				border-color: black;\n"
"}"));
        pushButton_unseenSignUp_1 = new QPushButton(centralwidget);
        pushButton_unseenSignUp_1->setObjectName(QString::fromUtf8("pushButton_unseenSignUp_1"));
        pushButton_unseenSignUp_1->setGeometry(QRect(340, 180, 30, 30));
        pushButton_unseenSignUp_1->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_unseenSignUp_1{\n"
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
"QPushButton#pushButton_unseenSignUp_1:hover {  \n"
"    /* \346\202\254\345\201\234\347\212\266\346\200\201\346\240\267"
                        "\345\274\217 */  \n"
"    background-color: rgba(100, 255, 100, 0.5); /* \346\267\241\347\273\277\350\211\262\357\274\214\345\215\212\351\200\217\346\230\216 */  \n"
"    /* \345\217\257\344\273\245\346\267\273\345\212\240\345\205\266\344\273\226\346\202\254\345\201\234\347\212\266\346\200\201\347\232\204\346\240\267\345\274\217 */  \n"
"}  \n"
"  \n"
"QPushButton#pushButton_unseenSignUp_1:pressed {  \n"
"    /* \346\214\211\344\270\213\347\212\266\346\200\201\346\240\267\345\274\217 */  \n"
"    background-color: rgb(0, 100, 0); /* \346\267\261\347\273\277\350\211\262 */  \n"
"    /* \345\217\257\344\273\245\346\267\273\345\212\240\345\205\266\344\273\226\346\214\211\344\270\213\347\212\266\346\200\201\347\232\204\346\240\267\345\274\217 */  \n"
"}\n"
""));
        pushButton_unseenSignUp_2 = new QPushButton(centralwidget);
        pushButton_unseenSignUp_2->setObjectName(QString::fromUtf8("pushButton_unseenSignUp_2"));
        pushButton_unseenSignUp_2->setGeometry(QRect(340, 230, 30, 30));
        pushButton_unseenSignUp_2->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_unseenSignUp_2{\n"
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
"QPushButton#pushButton_unseenSignUp_2:hover {  \n"
"    /* \346\202\254\345\201\234\347\212\266\346\200\201\346\240\267"
                        "\345\274\217 */  \n"
"    background-color: rgba(100, 255, 100, 0.5); /* \346\267\241\347\273\277\350\211\262\357\274\214\345\215\212\351\200\217\346\230\216 */  \n"
"    /* \345\217\257\344\273\245\346\267\273\345\212\240\345\205\266\344\273\226\346\202\254\345\201\234\347\212\266\346\200\201\347\232\204\346\240\267\345\274\217 */  \n"
"}  \n"
"  \n"
"QPushButton#pushButton_unseenSignUp_2:pressed {  \n"
"    /* \346\214\211\344\270\213\347\212\266\346\200\201\346\240\267\345\274\217 */  \n"
"    background-color: rgb(0, 100, 0); /* \346\267\261\347\273\277\350\211\262 */  \n"
"    /* \345\217\257\344\273\245\346\267\273\345\212\240\345\205\266\344\273\226\346\214\211\344\270\213\347\212\266\346\200\201\347\232\204\346\240\267\345\274\217 */  \n"
"}\n"
""));
        label_passwd2 = new QLabel(centralwidget);
        label_passwd2->setObjectName(QString::fromUtf8("label_passwd2"));
        label_passwd2->setGeometry(QRect(20, 230, 111, 31));
        pushButton_signupfinal = new QPushButton(centralwidget);
        pushButton_signupfinal->setObjectName(QString::fromUtf8("pushButton_signupfinal"));
        pushButton_signupfinal->setGeometry(QRect(40, 320, 101, 41));
        pushButton_signupfinal->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_signupfinal\n"
" {border-radius:18px;\n"
"        				  border-width: 1px;\n"
"        				  border-style: solid;\n"
"       					  border-color: black;\n"
"}\n"
"QPushButton#pushButton_signupfinal:hover {  \n"
"    /* \346\202\254\345\201\234\347\212\266\346\200\201\346\240\267\345\274\217 */  \n"
"    background-color: rgba(100, 255, 100, 0.5); /* \346\267\241\347\273\277\350\211\262\357\274\214\345\215\212\351\200\217\346\230\216 */  \n"
"    /* \345\217\257\344\273\245\346\267\273\345\212\240\345\205\266\344\273\226\346\202\254\345\201\234\347\212\266\346\200\201\347\232\204\346\240\267\345\274\217 */  \n"
"}  \n"
"  \n"
"QPushButton#pushButton_signupfinal:pressed {  \n"
"    /* \346\214\211\344\270\213\347\212\266\346\200\201\346\240\267\345\274\217 */  \n"
"    background-color: rgb(0, 100, 0); /* \346\267\261\347\273\277\350\211\262 */  \n"
"    /* \345\217\257\344\273\245\346\267\273\345\212\240\345\205\266\344\273\226\346\214\211\344\270\213\347\212\266\346\200\201\347\232\204\346"
                        "\240\267\345\274\217 */  \n"
"}"));
        backtomain = new QPushButton(centralwidget);
        backtomain->setObjectName(QString::fromUtf8("backtomain"));
        backtomain->setGeometry(QRect(210, 320, 101, 41));
        backtomain->setStyleSheet(QString::fromUtf8("QPushButton#backtomain\n"
" {border-radius:18px;\n"
"        				  border-width: 1px;\n"
"        				  border-style: solid;\n"
"       					  border-color: black;\n"
"}\n"
"QPushButton#backtomain:hover {  \n"
"    /* \346\202\254\345\201\234\347\212\266\346\200\201\346\240\267\345\274\217 */  \n"
"    background-color: rgba(100, 255, 100, 0.5); /* \346\267\241\347\273\277\350\211\262\357\274\214\345\215\212\351\200\217\346\230\216 */  \n"
"    /* \345\217\257\344\273\245\346\267\273\345\212\240\345\205\266\344\273\226\346\202\254\345\201\234\347\212\266\346\200\201\347\232\204\346\240\267\345\274\217 */  \n"
"}  \n"
"  \n"
"QPushButton#backtomain:pressed {  \n"
"    /* \346\214\211\344\270\213\347\212\266\346\200\201\346\240\267\345\274\217 */  \n"
"    background-color: rgb(0, 100, 0); /* \346\267\261\347\273\277\350\211\262 */  \n"
"    /* \345\217\257\344\273\245\346\267\273\345\212\240\345\205\266\344\273\226\346\214\211\344\270\213\347\212\266\346\200\201\347\232\204\346\240\267\345\274\217 */  \n"
"}"));
        checkBox_indicator = new QCheckBox(centralwidget);
        checkBox_indicator->setObjectName(QString::fromUtf8("checkBox_indicator"));
        checkBox_indicator->setGeometry(QRect(30, 280, 16, 16));
        checkBox_indicator->setCursor(QCursor(Qt::PointingHandCursor));
        checkBox_indicator->setStyleSheet(QString::fromUtf8("QCheckBox::#CheckBox_indicator {\n"
"    border: 1px solid black;\n"
"    width: 14px;\n"
"    height: 14px;\n"
"    border-radius: 8px;\n"
"    background-color: white; /* \351\273\230\350\256\244\350\203\214\346\231\257\350\211\262 */\n"
"};\n"
""));
        label_readme = new QLabel(centralwidget);
        label_readme->setObjectName(QString::fromUtf8("label_readme"));
        label_readme->setGeometry(QRect(60, 280, 251, 20));
        label_signup_right = new QLabel(centralwidget);
        label_signup_right->setObjectName(QString::fromUtf8("label_signup_right"));
        label_signup_right->setGeometry(QRect(380, -2, 221, 391));
        label_signup_right->setStyleSheet(QString::fromUtf8("border-image: url(:/images/SignUp_right.png);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 101, 31));
        lineEdit_nickname = new QLineEdit(centralwidget);
        lineEdit_nickname->setObjectName(QString::fromUtf8("lineEdit_nickname"));
        lineEdit_nickname->setGeometry(QRect(160, 60, 171, 31));
        lineEdit_nickname->setMinimumSize(QSize(0, 30));
        lineEdit_nickname->setStyleSheet(QString::fromUtf8("QLineEdit#lineEdit_nickname\n"
"{border-radius:14px;\n"
"					padding: 2 30 2 10;\n"
"        			border-width: 1px;\n"
"        			border-style: solid;\n"
"       				border-color: black;\n"
"}"));
        lineEdit_nickname->setMaxLength(30);
        SignUp->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SignUp);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 611, 17));
        SignUp->setMenuBar(menubar);
        statusbar = new QStatusBar(SignUp);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SignUp->setStatusBar(statusbar);

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QMainWindow *SignUp)
    {
        SignUp->setWindowTitle(QApplication::translate("SignUp", "MainWindow", nullptr));
        label_accountSignUp->setText(QApplication::translate("SignUp", "\346\226\260\350\264\246\345\217\267\346\263\250\345\206\214", nullptr));
        label_account1->setText(QApplication::translate("SignUp", "\350\264\246\345\217\267: ", nullptr));
        label_passwd1->setText(QApplication::translate("SignUp", "\345\257\206\347\240\201: ", nullptr));
        pushButton_unseenSignUp_1->setText(QString());
        pushButton_unseenSignUp_2->setText(QString());
        label_passwd2->setText(QApplication::translate("SignUp", "\345\206\215\346\254\241\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        pushButton_signupfinal->setText(QApplication::translate("SignUp", "\346\263\250\345\206\214", nullptr));
        backtomain->setText(QApplication::translate("SignUp", "\350\277\224\345\233\236", nullptr));
        checkBox_indicator->setText(QString());
        label_readme->setText(QString());
        label_signup_right->setText(QString());
        label->setText(QApplication::translate("SignUp", "\346\230\265\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
