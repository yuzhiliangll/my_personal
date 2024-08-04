/********************************************************************************
** Form generated from reading UI file 'afterlogin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AFTERLOGIN_H
#define UI_AFTERLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AfterLogin
{
public:
    QLabel *label_afterLoginImage;
    QLabel *label_afterLoginName;
    QPushButton *pushButton_changeHeaderimage;
    QPushButton *pushButton_back;
    QLabel *label_nickname;
    QPushButton *pushButton_enterMusicplayer;
    QLabel *label_AIchat;
    QPushButton *pushButton_AIchat;
    QPushButton *pushButton_onlinemusic;
    QLabel *label_AIgeneratedimage;

    void setupUi(QWidget *AfterLogin)
    {
        if (AfterLogin->objectName().isEmpty())
            AfterLogin->setObjectName(QString::fromUtf8("AfterLogin"));
        AfterLogin->resize(643, 341);
        AfterLogin->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 255, 255);"));
        label_afterLoginImage = new QLabel(AfterLogin);
        label_afterLoginImage->setObjectName(QString::fromUtf8("label_afterLoginImage"));
        label_afterLoginImage->setGeometry(QRect(10, 10, 141, 121));
        label_afterLoginImage->setStyleSheet(QString::fromUtf8(""));
        label_afterLoginName = new QLabel(AfterLogin);
        label_afterLoginName->setObjectName(QString::fromUtf8("label_afterLoginName"));
        label_afterLoginName->setGeometry(QRect(10, 220, 141, 31));
        label_afterLoginName->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_changeHeaderimage = new QPushButton(AfterLogin);
        pushButton_changeHeaderimage->setObjectName(QString::fromUtf8("pushButton_changeHeaderimage"));
        pushButton_changeHeaderimage->setGeometry(QRect(20, 280, 80, 31));
        pushButton_changeHeaderimage->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_changeHeaderimage\n"
"{\n"
"	border: 2px solid #4CAF50;\n"
"	border-radius: 10px;\n"
"	background-color: white;\n"
"}\n"
"QPushButton#pushButton_changeHeaderimage:hover\n"
"{\n"
"	background-color: #E8F5E9;\n"
"}\n"
"QPushButton#pushButton_changeHeaderimage:pressed\n"
"{\n"
"	background-color: #C8E6C9;\n"
"}\n"
""));
        pushButton_back = new QPushButton(AfterLogin);
        pushButton_back->setObjectName(QString::fromUtf8("pushButton_back"));
        pushButton_back->setGeometry(QRect(530, 280, 91, 31));
        pushButton_back->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_back\n"
"{\n"
"	border: 2px solid #4CAF50;\n"
"	border-radius: 10px;\n"
"	background-color: white;\n"
"}\n"
"QPushButton#pushButton_back:hover\n"
"{\n"
"	background-color: #E8F5E9;\n"
"}\n"
"QPushButton#pushButton_back:pressed\n"
"{\n"
"	background-color: #C8E6C9;\n"
"}"));
        label_nickname = new QLabel(AfterLogin);
        label_nickname->setObjectName(QString::fromUtf8("label_nickname"));
        label_nickname->setGeometry(QRect(10, 160, 141, 31));
        label_nickname->setStyleSheet(QString::fromUtf8(""));
        pushButton_enterMusicplayer = new QPushButton(AfterLogin);
        pushButton_enterMusicplayer->setObjectName(QString::fromUtf8("pushButton_enterMusicplayer"));
        pushButton_enterMusicplayer->setGeometry(QRect(300, 120, 101, 31));
        pushButton_enterMusicplayer->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_enterMusicplayer {  \n"
"    border: none; /* \346\210\226\350\200\205\345\256\214\345\205\250\347\234\201\347\225\245\350\277\231\350\241\214\357\274\214\345\233\240\344\270\272\346\262\241\346\234\211\350\256\276\347\275\256\350\276\271\346\241\206\345\256\275\345\272\246\345\222\214\346\240\267\345\274\217\357\274\214\345\256\203\351\273\230\350\256\244\344\270\272none */  \n"
"    border-radius: 10px; /* \350\256\276\347\275\256\345\234\206\350\247\222\350\276\271\346\241\206 */  \n"
"    background-color: rgba(255, 255, 255, 0); /* \350\256\276\347\275\256\344\270\272\351\200\217\346\230\216\350\203\214\346\231\257 */  \n"
"    color: black; /* \346\226\207\345\255\227\351\242\234\350\211\262 */  \n"
"}  \n"
"  \n"
"QPushButton#pushButton_enterMusicplayer:hover {  \n"
"    background-color: rgba(200, 255, 200, 0.5); /* \346\202\254\345\201\234\346\227\266\346\265\205\346\265\205\347\273\277\350\211\262 */  \n"
"}  \n"
"  \n"
"QPushButton#pushButton_enterMusicplayer:pressed {  \n"
" "
                        "   background-color: rgba(0, 255, 0, 0.5); /* \346\214\211\344\270\213\346\227\266\344\272\256\347\273\277\350\211\262 */  \n"
"}"));
        label_AIchat = new QLabel(AfterLogin);
        label_AIchat->setObjectName(QString::fromUtf8("label_AIchat"));
        label_AIchat->setGeometry(QRect(300, 200, 41, 31));
        label_AIchat->setStyleSheet(QString::fromUtf8("image: url(:/images/AI_chat.png);"));
        pushButton_AIchat = new QPushButton(AfterLogin);
        pushButton_AIchat->setObjectName(QString::fromUtf8("pushButton_AIchat"));
        pushButton_AIchat->setGeometry(QRect(340, 210, 61, 20));
        pushButton_AIchat->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_AIchat {  \n"
"    border: none; /* \346\210\226\350\200\205\345\256\214\345\205\250\347\234\201\347\225\245\350\277\231\350\241\214\357\274\214\345\233\240\344\270\272\346\262\241\346\234\211\350\256\276\347\275\256\350\276\271\346\241\206\345\256\275\345\272\246\345\222\214\346\240\267\345\274\217\357\274\214\345\256\203\351\273\230\350\256\244\344\270\272none */  \n"
"    border-radius: 10px; /* \350\256\276\347\275\256\345\234\206\350\247\222\350\276\271\346\241\206 */  \n"
"    background-color: rgba(255, 255, 255, 0); /* \350\256\276\347\275\256\344\270\272\351\200\217\346\230\216\350\203\214\346\231\257 */  \n"
"    color: black; /* \346\226\207\345\255\227\351\242\234\350\211\262 */  \n"
"}  \n"
"  \n"
"QPushButton#pushButton_AIchat:hover {  \n"
"    background-color: rgba(200, 255, 200, 0.5); /* \346\202\254\345\201\234\346\227\266\346\265\205\346\265\205\347\273\277\350\211\262 */  \n"
"}  \n"
"  \n"
"QPushButton#pushButton_AIchat:pressed {  \n"
"    background-color: rgba(0, 2"
                        "55, 0, 0.5); /* \346\214\211\344\270\213\346\227\266\344\272\256\347\273\277\350\211\262 */  \n"
"}"));
        pushButton_onlinemusic = new QPushButton(AfterLogin);
        pushButton_onlinemusic->setObjectName(QString::fromUtf8("pushButton_onlinemusic"));
        pushButton_onlinemusic->setGeometry(QRect(300, 50, 101, 31));
        pushButton_onlinemusic->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_onlinemusic {  \n"
"    border: none; /* \346\210\226\350\200\205\345\256\214\345\205\250\347\234\201\347\225\245\350\277\231\350\241\214\357\274\214\345\233\240\344\270\272\346\262\241\346\234\211\350\256\276\347\275\256\350\276\271\346\241\206\345\256\275\345\272\246\345\222\214\346\240\267\345\274\217\357\274\214\345\256\203\351\273\230\350\256\244\344\270\272none */  \n"
"    border-radius: 10px; /* \350\256\276\347\275\256\345\234\206\350\247\222\350\276\271\346\241\206 */  \n"
"    background-color: rgba(255, 255, 255, 0); /* \350\256\276\347\275\256\344\270\272\351\200\217\346\230\216\350\203\214\346\231\257 */  \n"
"    color: black; /* \346\226\207\345\255\227\351\242\234\350\211\262 */  \n"
"}  \n"
"  \n"
"QPushButton#pushButton_onlinemusic:hover {  \n"
"    background-color: rgba(200, 255, 200, 0.5); /* \346\202\254\345\201\234\346\227\266\346\265\205\346\265\205\347\273\277\350\211\262 */  \n"
"}  \n"
"  \n"
"QPushButton#pushButton_onlinemusic:pressed {  \n"
"    background-c"
                        "olor: rgba(0, 255, 0, 0.5); /* \346\214\211\344\270\213\346\227\266\344\272\256\347\273\277\350\211\262 */  \n"
"}"));
        label_AIgeneratedimage = new QLabel(AfterLogin);
        label_AIgeneratedimage->setObjectName(QString::fromUtf8("label_AIgeneratedimage"));
        label_AIgeneratedimage->setGeometry(QRect(410, 40, 211, 211));

        retranslateUi(AfterLogin);

        QMetaObject::connectSlotsByName(AfterLogin);
    } // setupUi

    void retranslateUi(QWidget *AfterLogin)
    {
        AfterLogin->setWindowTitle(QApplication::translate("AfterLogin", "Form", nullptr));
        label_afterLoginImage->setText(QString());
        label_afterLoginName->setText(QString());
        pushButton_changeHeaderimage->setText(QApplication::translate("AfterLogin", "\346\233\264\346\224\271\345\244\264\345\203\217", nullptr));
        pushButton_back->setText(QApplication::translate("AfterLogin", "\350\277\224\345\233\236", nullptr));
        label_nickname->setText(QString());
        pushButton_enterMusicplayer->setText(QApplication::translate("AfterLogin", "\346\234\254\345\234\260\345\222\214\344\270\213\350\275\275", nullptr));
        label_AIchat->setText(QString());
        pushButton_AIchat->setText(QApplication::translate("AfterLogin", "AI\345\212\251\346\211\213", nullptr));
        pushButton_onlinemusic->setText(QApplication::translate("AfterLogin", "\345\234\250\347\272\277\344\272\221\351\237\263\344\271\220", nullptr));
        label_AIgeneratedimage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AfterLogin: public Ui_AfterLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AFTERLOGIN_H
