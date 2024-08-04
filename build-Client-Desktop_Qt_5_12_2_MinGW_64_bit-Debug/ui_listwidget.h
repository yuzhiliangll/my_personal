/********************************************************************************
** Form generated from reading UI file 'listwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTWIDGET_H
#define UI_LISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListWidget
{
public:
    QLabel *label_gif;
    QLabel *Onlinebaidu;
    QListWidget *Onlinemusicposter;
    QLabel *Onlinelabel_CurrentTime;
    QPushButton *OnlinePlay;
    QPushButton *OnlineNext;
    QSlider *OnlineverticalSlider;
    QSlider *OnlinehorizontalSlider;
    QPushButton *OnlinepushButton_playmode;
    QLabel *Onlinelabel_updateVolume;
    QLabel *Onlinelabel_TotalTime;
    QWidget *widget;
    QLabel *OnlineLRC_1;
    QLabel *OnlineLRC;
    QLabel *OnlineLRC_2;
    QLabel *OnlineLRC_3;
    QLabel *OnlineLRC_4;
    QLabel *OnlineLRC_5;
    QLabel *OnlineLRC_6;
    QPushButton *OnlinePrev;
    QPushButton *OnlinepushButton_volume;
    QPushButton *onlineMusicPlay;
    QTableWidget *tableWidget;
    QPushButton *OnlineLRCShow;
    QLabel *label_currentPlayMusic;
    QPushButton *pushButton_myLikeMusic;
    QPushButton *pushButton_myLikeMusicList;

    void setupUi(QWidget *ListWidget)
    {
        if (ListWidget->objectName().isEmpty())
            ListWidget->setObjectName(QString::fromUtf8("ListWidget"));
        ListWidget->resize(982, 477);
        label_gif = new QLabel(ListWidget);
        label_gif->setObjectName(QString::fromUtf8("label_gif"));
        label_gif->setGeometry(QRect(880, 0, 101, 51));
        label_gif->setStyleSheet(QString::fromUtf8("QLabel#label_gif\n"
"{\n"
"    border: 2px solid white; /* \350\256\276\347\275\256\347\231\275\350\211\262\350\276\271\346\241\206 */\n"
"    background-color: white; /* \351\273\230\350\256\244\350\203\214\346\231\257\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262 */\n"
"    border-radius: 5px; /* \350\256\276\347\275\256\345\234\206\350\247\222 */\n"
"    padding: 5px 10px; /* \345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QLabel#label_gif:hover {\n"
"    border-color: white; /* \346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\344\270\272\347\231\275\350\211\262 */\n"
"    background-color: lightyellow; /* \346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\344\270\272\346\265\205\351\273\204\350\211\262 */\n"
"}"));
        Onlinebaidu = new QLabel(ListWidget);
        Onlinebaidu->setObjectName(QString::fromUtf8("Onlinebaidu"));
        Onlinebaidu->setGeometry(QRect(880, 50, 61, 31));
        Onlinebaidu->setStyleSheet(QString::fromUtf8("QLabel#Onlinebaidu \n"
"{\n"
"    border: 2px solid green; /* \350\256\276\347\275\256\347\273\277\350\211\262\350\276\271\346\241\206 */\n"
"    background-color: white; /* \351\273\230\350\256\244\350\203\214\346\231\257\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262 */\n"
"    border-radius: 10px; /* \350\256\276\347\275\256\345\234\206\350\247\222 */\n"
"    padding: 5px 10px; /* \345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QLabel#Onlinebaidu:hover {\n"
"    border-color: lightgreen; /* \346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\344\270\272\346\265\205\347\273\277\350\211\262 */\n"
"    background-color: lightgreen; /* \346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\344\270\272\346\265\205\347\273\277\350\211\262 */\n"
"}\n"
""));
        Onlinemusicposter = new QListWidget(ListWidget);
        Onlinemusicposter->setObjectName(QString::fromUtf8("Onlinemusicposter"));
        Onlinemusicposter->setGeometry(QRect(180, 300, 221, 151));
        Onlinemusicposter->setStyleSheet(QString::fromUtf8("QListWidget#Onlinemusicposter\n"
"{\n"
"    background: transparent;\n"
"	border: none;\n"
"}\n"
""));
        Onlinelabel_CurrentTime = new QLabel(ListWidget);
        Onlinelabel_CurrentTime->setObjectName(QString::fromUtf8("Onlinelabel_CurrentTime"));
        Onlinelabel_CurrentTime->setGeometry(QRect(420, 360, 41, 21));
        Onlinelabel_CurrentTime->setStyleSheet(QString::fromUtf8(""));
        OnlinePlay = new QPushButton(ListWidget);
        OnlinePlay->setObjectName(QString::fromUtf8("OnlinePlay"));
        OnlinePlay->setGeometry(QRect(580, 400, 31, 31));
        OnlinePlay->setStyleSheet(QString::fromUtf8("QPushButton#OnlinePlay \n"
"{\n"
"    background-color: lightgreen;\n"
"    border-radius: 15px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: white; /* \344\275\277\346\226\207\346\234\254\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262\357\274\214\347\241\256\344\277\235\345\234\250\346\267\261\347\273\277\350\211\262\350\203\214\346\231\257\344\270\212\345\217\257\350\247\201 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"QPushButton#OnlinePlay:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262\357\274\214\345\217\257\344\273\245\346"
                        "\257\224\346\265\205\347\273\277\350\211\262\346\233\264\346\232\227 */\n"
"}\n"
""));
        OnlineNext = new QPushButton(ListWidget);
        OnlineNext->setObjectName(QString::fromUtf8("OnlineNext"));
        OnlineNext->setGeometry(QRect(630, 400, 31, 31));
        OnlineNext->setStyleSheet(QString::fromUtf8("QPushButton#OnlineNext \n"
"{\n"
"    background-color: white; /* \345\210\235\345\247\213\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border-radius: 15px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: black; /* \345\210\235\345\247\213\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"    border: 2px solid #90ee90; /* \345\210\235\345\247\213\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#OnlineNext:hover \n"
"{\n"
"    background-color: lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211"
                        "\262 */\n"
"    border: 2px solid lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: white; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#OnlineNext:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
""));
        OnlineverticalSlider = new QSlider(ListWidget);
        OnlineverticalSlider->setObjectName(QString::fromUtf8("OnlineverticalSlider"));
        OnlineverticalSlider->setGeometry(QRect(780, 320, 16, 71));
        OnlineverticalSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:vertical \n"
"{\n"
"    border: 1px solid #999999;\n"
"    background: white; /* \350\203\214\346\231\257\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262 */\n"
"    width: 5px; /* \346\273\221\346\247\275\347\232\204\345\256\275\345\272\246 */\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:vertical \n"
"{\n"
"    background: white; /* \346\273\221\345\235\227\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262 */\n"
"    border: 1px solid #5c5c5c;\n"
"    height: 10px; /* \346\273\221\345\235\227\347\232\204\351\253\230\345\272\246 */\n"
"    margin: -3px -3px; /* \346\216\247\345\210\266\346\273\221\345\235\227\347\232\204\345\256\275\345\272\246\345\222\214\344\275\215\347\275\256 */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QSlider::add-page:vertical \n"
"{\n"
"    background: #9ACD32; /* \347\250\215\345\276\256\346\267\261\344\270\200\347\202\271\347\232\204\347\273\277\350\211\262 */\n"
"    border: 1px solid #777;\n"
"    width: 10px;\n"
"    border-radiu"
                        "s: 4px;\n"
"}\n"
"QSlider::sub-page:vertical \n"
"{\n"
"    background: white; /* \346\234\252\346\273\221\345\212\250\351\203\250\345\210\206\347\232\204\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262 */\n"
"    border: 1px solid #999999;\n"
"    width: 10px;\n"
"    border-radius: 4px;\n"
"}\n"
"QSlider::handle:vertical:hover \n"
"{\n"
"    background: #cccccc; /* \346\202\254\345\201\234\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 1px solid #5c5c5c;\n"
"}\n"
"\n"
"\n"
""));
        OnlineverticalSlider->setOrientation(Qt::Vertical);
        OnlinehorizontalSlider = new QSlider(ListWidget);
        OnlinehorizontalSlider->setObjectName(QString::fromUtf8("OnlinehorizontalSlider"));
        OnlinehorizontalSlider->setGeometry(QRect(420, 380, 321, 20));
        OnlinehorizontalSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border: 1px solid #bbb;\n"
"    background: white;\n"
"    height: 10px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,\n"
"        stop: 0 #66e,\n"
"        stop: 1 #bbf);\n"
"    border: 1px solid #777;\n"
"    height: 10px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"    background: #fff;\n"
"    border: 1px solid #777;\n"
"    height: 10px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qradialgradient(spread: pad, cx: 0.5, cy: 0.5, radius: 0.5, fx: 0.5, fy: 0.5,\n"
"        stop: 0.6 #45ADED,\n"
"        stop: 0.778409 rgba(255, 255, 255, 255));\n"
"    border: 1px solid #777;\n"
"    border-radius: 6px;\n"
"    width: 13px;\n"
"    margin-top: -2px;\n"
"    margin-bottom: -2px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"    background: qradialgradient(spread: pad, cx: 0.5, cy: 0.5, radius: "
                        "0.5, fx: 0.5, fy: 0.5,\n"
"        stop: 0.6 #2A8BDA,\n"
"        stop: 0.778409 rgba(255, 255, 255, 255));\n"
"    border: 1px solid #444;\n"
"    border-radius: 6px;\n"
"}\n"
""));
        OnlinehorizontalSlider->setOrientation(Qt::Horizontal);
        OnlinepushButton_playmode = new QPushButton(ListWidget);
        OnlinepushButton_playmode->setObjectName(QString::fromUtf8("OnlinepushButton_playmode"));
        OnlinepushButton_playmode->setGeometry(QRect(420, 410, 31, 31));
        OnlinepushButton_playmode->setStyleSheet(QString::fromUtf8("QPushButton#OnlinepushButton_playmode \n"
"{\n"
"    border-radius: 10px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: black; /* \345\210\235\345\247\213\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"    border: 2px solid #90ee90; /* \345\210\235\345\247\213\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#OnlinepushButton_playmode:hover \n"
"{\n"
"    background-color: lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid lightgreen; /* \351\274\240\346\240\207\346\202"
                        "\254\345\201\234\346\227\266\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: white; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#OnlinepushButton_playmode:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}"));
        Onlinelabel_updateVolume = new QLabel(ListWidget);
        Onlinelabel_updateVolume->setObjectName(QString::fromUtf8("Onlinelabel_updateVolume"));
        Onlinelabel_updateVolume->setGeometry(QRect(790, 390, 34, 34));
        Onlinelabel_updateVolume->setStyleSheet(QString::fromUtf8("QLabel#Onlinelabel_updateVolume {\n"
"    text-align: center; /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"}\n"
"\n"
""));
        Onlinelabel_TotalTime = new QLabel(ListWidget);
        Onlinelabel_TotalTime->setObjectName(QString::fromUtf8("Onlinelabel_TotalTime"));
        Onlinelabel_TotalTime->setGeometry(QRect(720, 360, 41, 21));
        widget = new QWidget(ListWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(530, 90, 421, 211));
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget \n"
"{\n"
"    background-image: url(:/image/LRC_background_image.png);\n"
"    background-attachment: fixed; /* \347\241\256\344\277\235\350\203\214\346\231\257\345\233\276\345\203\217\345\233\272\345\256\232\344\270\215\345\212\250 */\n"
"    background-position: center; /* \345\233\276\345\203\217\345\234\250\346\216\247\344\273\266\344\270\255\345\261\205\344\270\255 */\n"
"    background-repeat: no-repeat; /* \344\270\215\351\207\215\345\244\215\346\230\276\347\244\272\350\203\214\346\231\257\345\233\276\345\203\217 */\n"
"}\n"
"\n"
""));
        OnlineLRC_1 = new QLabel(widget);
        OnlineLRC_1->setObjectName(QString::fromUtf8("OnlineLRC_1"));
        OnlineLRC_1->setGeometry(QRect(0, 40, 421, 16));
        OnlineLRC_1->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";\n"
""));
        OnlineLRC = new QLabel(widget);
        OnlineLRC->setObjectName(QString::fromUtf8("OnlineLRC"));
        OnlineLRC->setGeometry(QRect(0, 10, 421, 16));
        OnlineLRC->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";\n"
"QLabel#label_LRC \n"
"{\n"
"    border: 0px;\n"
"}\n"
""));
        OnlineLRC_2 = new QLabel(widget);
        OnlineLRC_2->setObjectName(QString::fromUtf8("OnlineLRC_2"));
        OnlineLRC_2->setGeometry(QRect(0, 70, 421, 16));
        OnlineLRC_2->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";"));
        OnlineLRC_3 = new QLabel(widget);
        OnlineLRC_3->setObjectName(QString::fromUtf8("OnlineLRC_3"));
        OnlineLRC_3->setGeometry(QRect(0, 100, 421, 16));
        OnlineLRC_3->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";"));
        OnlineLRC_4 = new QLabel(widget);
        OnlineLRC_4->setObjectName(QString::fromUtf8("OnlineLRC_4"));
        OnlineLRC_4->setGeometry(QRect(0, 130, 421, 16));
        OnlineLRC_4->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";"));
        OnlineLRC_5 = new QLabel(widget);
        OnlineLRC_5->setObjectName(QString::fromUtf8("OnlineLRC_5"));
        OnlineLRC_5->setGeometry(QRect(0, 160, 421, 16));
        OnlineLRC_5->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";"));
        OnlineLRC_6 = new QLabel(widget);
        OnlineLRC_6->setObjectName(QString::fromUtf8("OnlineLRC_6"));
        OnlineLRC_6->setGeometry(QRect(0, 190, 421, 16));
        OnlinePrev = new QPushButton(ListWidget);
        OnlinePrev->setObjectName(QString::fromUtf8("OnlinePrev"));
        OnlinePrev->setGeometry(QRect(530, 400, 31, 31));
        OnlinePrev->setStyleSheet(QString::fromUtf8("QPushButton#OnlinePrev \n"
"{\n"
"    background-color: white; /* \345\210\235\345\247\213\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border-radius: 15px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: black; /* \345\210\235\345\247\213\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"    border: 2px solid #90ee90; /* \345\210\235\345\247\213\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#OnlinePrev:hover \n"
"{\n"
"    background-color: lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211"
                        "\262 */\n"
"    border: 2px solid lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: white; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#OnlinePrev:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
""));
        OnlinepushButton_volume = new QPushButton(ListWidget);
        OnlinepushButton_volume->setObjectName(QString::fromUtf8("OnlinepushButton_volume"));
        OnlinepushButton_volume->setGeometry(QRect(750, 390, 31, 31));
        OnlinepushButton_volume->setStyleSheet(QString::fromUtf8("QPushButton#OnlinepushButton_volume \n"
"{\n"
"    border: none;\n"
"    background-color: transparent; /* \346\270\205\351\231\244\351\273\230\350\256\244\350\203\214\346\231\257\350\211\262 */\n"
"    /* width: 70px; /* \350\256\276\347\275\256\346\214\211\351\222\256\345\256\275\345\272\246 */\n"
"    /* height: 70px; /* \350\256\276\347\275\256\346\214\211\351\222\256\351\253\230\345\272\246 */\n"
"    border-radius: 15px; /* \345\234\206\345\275\242\346\214\211\351\222\256\357\274\214\345\215\212\345\276\204\344\270\272\345\256\275\345\272\246\346\210\226\351\253\230\345\272\246\347\232\204\344\270\200\345\215\212 */\n"
"    /* padding: 10px; /* \345\217\257\351\200\211\357\274\232\350\256\276\347\275\256\345\206\205\350\276\271\350\267\235\344\273\245\346\216\247\345\210\266\346\214\211\351\222\256\345\244\247\345\260\217 */\n"
"	border: 2px solid rgb(144, 238, 144); /* \346\267\273\345\212\240\346\265\205\347\273\277\350\211\262\350\276\271\346\241\206 */\n"
"}\n"
"QPushButton#OnlinepushButton_volume::h"
                        "over\n"
"{\n"
"	background-color: rgb(56, 255, 21);\n"
"};"));
        onlineMusicPlay = new QPushButton(ListWidget);
        onlineMusicPlay->setObjectName(QString::fromUtf8("onlineMusicPlay"));
        onlineMusicPlay->setGeometry(QRect(0, 50, 111, 31));
        onlineMusicPlay->setStyleSheet(QString::fromUtf8("QPushButton#onlineMusicPlay\n"
"{\n"
"    background: transparent;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton#onlineMusicPlay:hover \n"
"{\n"
"    background-color: lightgreen;\n"
"}\n"
""));
        tableWidget = new QTableWidget(ListWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(120, 10, 401, 281));
        OnlineLRCShow = new QPushButton(ListWidget);
        OnlineLRCShow->setObjectName(QString::fromUtf8("OnlineLRCShow"));
        OnlineLRCShow->setGeometry(QRect(700, 410, 31, 31));
        OnlineLRCShow->setStyleSheet(QString::fromUtf8("QPushButton#OnlineLRCShow\n"
"{\n"
"	border-image: url(:/image/LRCShow.png);\n"
"    background-color: white; /* \345\210\235\345\247\213\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border-radius: 15px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: black; /* \345\210\235\345\247\213\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"    border: 2px solid #90ee90; /* \345\210\235\345\247\213\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#OnlineLRCShow:hover \n"
"{\n"
"    background-color: lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347"
                        "\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: white; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#OnlineLRCShow:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
""));
        label_currentPlayMusic = new QLabel(ListWidget);
        label_currentPlayMusic->setObjectName(QString::fromUtf8("label_currentPlayMusic"));
        label_currentPlayMusic->setGeometry(QRect(460, 360, 171, 20));
        pushButton_myLikeMusic = new QPushButton(ListWidget);
        pushButton_myLikeMusic->setObjectName(QString::fromUtf8("pushButton_myLikeMusic"));
        pushButton_myLikeMusic->setGeometry(QRect(480, 410, 31, 31));
        pushButton_myLikeMusic->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_myLikeMusic {\n"
"    border: 2px solid #ffcccc; /* \345\210\235\345\247\213\350\276\271\346\241\206\351\242\234\350\211\262\344\270\272\346\267\241\347\272\242\350\211\262 */\n"
"    border-radius: 15px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    background-color: #ffffff; /* \350\203\214\346\231\257\350\211\262\347\231\275\350\211\262 */\n"
"	background-position: center;/* \345\233\276\346\240\207\345\261\205\344\270\255 */\n"
"}\n"
"QPushButton#pushButton_myLikeMusic::hover \n"
"{\n"
"    border: 2px solid #ff0000;/* \346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262\344\270\272\346\267\261\347\272\242\350\211\262 */\n"
"}\n"
"QPushButton#pushButton_myLikeMusic::pressed \n"
"{\n"
"    background-color: #ff0000; /* \346\214\211\351\222\256\346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242"
                        "\234\350\211\262\344\270\272\346\267\261\347\272\242\350\211\262 */\n"
"}"));
        pushButton_myLikeMusicList = new QPushButton(ListWidget);
        pushButton_myLikeMusicList->setObjectName(QString::fromUtf8("pushButton_myLikeMusicList"));
        pushButton_myLikeMusicList->setGeometry(QRect(0, 110, 111, 31));
        pushButton_myLikeMusicList->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_myLikeMusicList\n"
"{\n"
"    background: transparent;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton#pushButton_myLikeMusicList:hover \n"
"{\n"
"    background-color: lightgreen;\n"
"}"));

        retranslateUi(ListWidget);

        QMetaObject::connectSlotsByName(ListWidget);
    } // setupUi

    void retranslateUi(QWidget *ListWidget)
    {
        ListWidget->setWindowTitle(QApplication::translate("ListWidget", "Form", nullptr));
        label_gif->setText(QString());
        Onlinebaidu->setText(QString());
        Onlinelabel_CurrentTime->setText(QApplication::translate("ListWidget", "0.0", nullptr));
        OnlinePlay->setText(QString());
        OnlineNext->setText(QString());
        OnlinepushButton_playmode->setText(QString());
        Onlinelabel_updateVolume->setText(QString());
        Onlinelabel_TotalTime->setText(QApplication::translate("ListWidget", "0.0", nullptr));
        OnlineLRC_1->setText(QString());
        OnlineLRC->setText(QString());
        OnlineLRC_2->setText(QString());
        OnlineLRC_3->setText(QString());
        OnlineLRC_4->setText(QString());
        OnlineLRC_5->setText(QString());
        OnlineLRC_6->setText(QString());
        OnlinePrev->setText(QString());
        OnlinepushButton_volume->setText(QString());
        onlineMusicPlay->setText(QApplication::translate("ListWidget", "\345\234\250\347\272\277\351\237\263\344\271\220\346\222\255\346\224\276", nullptr));
        OnlineLRCShow->setText(QString());
        label_currentPlayMusic->setText(QString());
        pushButton_myLikeMusic->setText(QString());
        pushButton_myLikeMusicList->setText(QApplication::translate("ListWidget", "\346\210\221\345\226\234\346\254\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListWidget: public Ui_ListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTWIDGET_H
