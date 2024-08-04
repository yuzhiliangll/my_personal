/********************************************************************************
** Form generated from reading UI file 'http.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTTP_H
#define UI_HTTP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HTTP
{
public:
    QPushButton *pushButton_image;
    QLabel *label_image;
    QPushButton *pushButton;
    QTextEdit *textEdit_send;
    QTextEdit *textEdit_reply;

    void setupUi(QWidget *HTTP)
    {
        if (HTTP->objectName().isEmpty())
            HTTP->setObjectName(QString::fromUtf8("HTTP"));
        HTTP->resize(873, 446);
        pushButton_image = new QPushButton(HTTP);
        pushButton_image->setObjectName(QString::fromUtf8("pushButton_image"));
        pushButton_image->setGeometry(QRect(680, 360, 61, 31));
        pushButton_image->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_image\n"
"{\n"
"    border: none;       /*\346\227\240\350\276\271\346\241\206*/\n"
"    background: transparent;/*\350\203\214\346\231\257\351\200\217\346\230\216*/\n"
"    border-radius: 15px;/*\345\234\206\350\247\222\345\215\212\345\276\204\357\274\210\346\240\271\346\215\256\346\214\211\351\222\256\345\244\247\345\260\217\350\260\203\346\225\264\357\274\211*/\n"
"}\n"
"QPushButton#pushButton_image:hover \n"
"{\n"
"    background-color: lightgreen;/*\346\202\254\345\201\234\346\227\266\344\270\272\347\273\277\350\211\262*/\n"
"}\n"
"QPushButton#pushButton_image:pressed \n"
"{\n"
"     background-color: darkgreen;/*\346\214\211\344\270\213\346\227\266\344\270\272\346\267\261\347\273\277\350\211\262*/\n"
"}"));
        label_image = new QLabel(HTTP);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        label_image->setGeometry(QRect(400, 20, 431, 321));
        pushButton = new QPushButton(HTTP);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(380, 360, 61, 31));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton#pushButton\n"
"{\n"
"    border: none;       /*\346\227\240\350\276\271\346\241\206*/\n"
"    background: transparent;/*\350\203\214\346\231\257\351\200\217\346\230\216*/\n"
"    border-radius: 15px;/*\345\234\206\350\247\222\345\215\212\345\276\204\357\274\210\346\240\271\346\215\256\346\214\211\351\222\256\345\244\247\345\260\217\350\260\203\346\225\264\357\274\211*/\n"
"}\n"
"QPushButton#pushButton:hover \n"
"{\n"
"    background-color: lightgreen;/*\346\202\254\345\201\234\346\227\266\344\270\272\347\273\277\350\211\262*/\n"
"}\n"
"QPushButton#pushButton:pressed \n"
"{\n"
"     background-color: darkgreen;/*\346\214\211\344\270\213\346\227\266\344\270\272\346\267\261\347\273\277\350\211\262*/\n"
"}"));
        textEdit_send = new QTextEdit(HTTP);
        textEdit_send->setObjectName(QString::fromUtf8("textEdit_send"));
        textEdit_send->setGeometry(QRect(10, 250, 361, 151));
        textEdit_reply = new QTextEdit(HTTP);
        textEdit_reply->setObjectName(QString::fromUtf8("textEdit_reply"));
        textEdit_reply->setGeometry(QRect(10, 60, 361, 171));
        textEdit_reply->setStyleSheet(QString::fromUtf8("QTextEdit#textEdit_reply\n"
"{\n"
"    border: none;       /*\346\227\240\350\276\271\346\241\206*/\n"
"    background: transparent;/*\350\203\214\346\231\257\351\200\217\346\230\216*/\n"
"}"));

        retranslateUi(HTTP);

        QMetaObject::connectSlotsByName(HTTP);
    } // setupUi

    void retranslateUi(QWidget *HTTP)
    {
        HTTP->setWindowTitle(QApplication::translate("HTTP", "HTTP", nullptr));
        pushButton_image->setText(QApplication::translate("HTTP", "\347\224\237\346\210\220", nullptr));
        label_image->setText(QString());
        pushButton->setText(QApplication::translate("HTTP", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HTTP: public Ui_HTTP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTTP_H
