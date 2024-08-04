/********************************************************************************
** Form generated from reading UI file 'netcon.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETCON_H
#define UI_NETCON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetCon
{
public:
    QPushButton *Sure;
    QPushButton *Cancel;
    QLabel *label_IP;
    QLabel *label_PORT;
    QLineEdit *lineEdit_IP;
    QLineEdit *lineEdit_PORT;

    void setupUi(QWidget *NetCon)
    {
        if (NetCon->objectName().isEmpty())
            NetCon->setObjectName(QString::fromUtf8("NetCon"));
        NetCon->resize(400, 300);
        Sure = new QPushButton(NetCon);
        Sure->setObjectName(QString::fromUtf8("Sure"));
        Sure->setGeometry(QRect(180, 204, 51, 31));
        Sure->setStyleSheet(QString::fromUtf8("QPushButton#Sure{\n"
"background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0, \n"
"stop:0.0112994 rgba(210, 188, 235, 255), \n"
"stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(50, 50, 50);\n"
" \n"
"border:0px groove gray;border-radius:7px;\n"
"padding:2px 4px;\n"
"font: 11pt \"\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)\";\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton#Sure:hover {\n"
"    background-color: lightgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250hover\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"QPushButton#Sure:pressed {\n"
"    background-color: darkgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250pressed\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}"));
        Cancel = new QPushButton(NetCon);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        Cancel->setGeometry(QRect(250, 204, 51, 31));
        Cancel->setStyleSheet(QString::fromUtf8("QPushButton#Cancel{\n"
"background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0, \n"
"stop:0.0112994 rgba(210, 188, 235, 255), \n"
"stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(50, 50, 50);\n"
" \n"
"border:0px groove gray;border-radius:7px;\n"
"padding:2px 4px;\n"
"font: 11pt \"\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)\";\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton#Cancel:hover {\n"
"    background-color: lightgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250hover\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"QPushButton#Cancel:pressed {\n"
"    background-color: darkgreen;\n"
"    color: white;\n"
"	border-radius: 10px; /* \347\241\256\344\277\235\345\234\250pressed\347\212\266\346\200\201\344\270\213\344\271\237\346\234\211\347\233\270\345\220\214\347\232\204\345\234\206\350\247\222 */\n"
"}"));
        label_IP = new QLabel(NetCon);
        label_IP->setObjectName(QString::fromUtf8("label_IP"));
        label_IP->setGeometry(QRect(80, 70, 51, 31));
        label_IP->setStyleSheet(QString::fromUtf8("QLabel#label_IP {\n"
"    background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0, \n"
"                                      stop:0.0112994 rgba(173, 216, 230, 255), \n"
"                                      stop:1 rgba(255, 255, 255, 255));\n"
"    color: rgb(50, 50, 50);\n"
"    border: 0px groove gray;\n"
"    border-radius: 7px;\n"
"    padding: 2px 4px;\n"
"    font: 10pt \"\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)\";\n"
"}"));
        label_PORT = new QLabel(NetCon);
        label_PORT->setObjectName(QString::fromUtf8("label_PORT"));
        label_PORT->setGeometry(QRect(80, 120, 51, 31));
        label_PORT->setStyleSheet(QString::fromUtf8("QLabel#label_PORT {\n"
"    background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0, \n"
"                                      stop:0.0112994 rgba(173, 216, 230, 255), \n"
"                                      stop:1 rgba(255, 255, 255, 255));\n"
"    color: rgb(50, 50, 50);\n"
"    border: 0px groove gray;\n"
"    border-radius: 7px;\n"
"    padding: 2px 4px;\n"
"    font: 10pt \"\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)\";\n"
"}"));
        lineEdit_IP = new QLineEdit(NetCon);
        lineEdit_IP->setObjectName(QString::fromUtf8("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(140, 70, 171, 31));
        lineEdit_IP->setStyleSheet(QString::fromUtf8("QLineEdit#lineEdit_IP {\n"
"    background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0, \n"
"                                      stop:0.0112994 rgba(173, 216, 230, 255), \n"
"                                      stop:1 rgba(255, 255, 255, 255));\n"
"    color: rgb(50, 50, 50);\n"
"    border: 0px groove gray;\n"
"    border-radius: 7px;\n"
"    padding: 2px 4px;\n"
"    font: 14pt \"\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)\";\n"
"}"));
        lineEdit_PORT = new QLineEdit(NetCon);
        lineEdit_PORT->setObjectName(QString::fromUtf8("lineEdit_PORT"));
        lineEdit_PORT->setGeometry(QRect(140, 120, 171, 31));
        lineEdit_PORT->setStyleSheet(QString::fromUtf8("QLineEdit#lineEdit_PORT {\n"
"    background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0, \n"
"                                      stop:0.0112994 rgba(173, 216, 230, 255), \n"
"                                      stop:1 rgba(255, 255, 255, 255));\n"
"    color: rgb(50, 50, 50);\n"
"    border: 0px groove gray;\n"
"    border-radius: 7px;\n"
"    padding: 2px 4px;\n"
"    font: 14pt \"\345\215\216\345\272\267\346\226\271\345\234\206\344\275\223W7(P)\";\n"
"}"));

        retranslateUi(NetCon);

        QMetaObject::connectSlotsByName(NetCon);
    } // setupUi

    void retranslateUi(QWidget *NetCon)
    {
        NetCon->setWindowTitle(QApplication::translate("NetCon", "Form", nullptr));
        Sure->setText(QApplication::translate("NetCon", "\347\241\256\350\256\244", nullptr));
        Cancel->setText(QApplication::translate("NetCon", "\345\217\226\346\266\210", nullptr));
        label_IP->setText(QApplication::translate("NetCon", "IP", nullptr));
        label_PORT->setText(QApplication::translate("NetCon", "PORT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetCon: public Ui_NetCon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETCON_H
