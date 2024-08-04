/********************************************************************************
** Form generated from reading UI file 'musicplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICPLAYER_H
#define UI_MUSICPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicPlayer
{
public:
    QLabel *label_CurrentTime;
    QLabel *label_TotalTime;
    QWidget *widget;
    QLabel *label_LRC_1;
    QLabel *label_LRC;
    QLabel *label_LRC_2;
    QLabel *label_LRC_3;
    QLabel *label_LRC_4;
    QLabel *label_LRC_5;
    QLabel *label_LRC_6;
    QSlider *horizontalSlider;
    QListWidget *listWidget;
    QPushButton *Play;
    QPushButton *Next;
    QPushButton *Prev;
    QSlider *verticalSlider;
    QPushButton *pushButton_volume;
    QLabel *label_updateVolume;
    QLabel *label_baidu;
    QLabel *label_gif_one;
    QListWidget *listWidget_musicposter;
    QPushButton *pushButton_playmode;
    QPushButton *pushButton_downloadmusic;
    QPushButton *showDownloadListButton;
    QPushButton *showDownloadListPlayButton;
    QLabel *label_currentPlayMusicName;
    QPushButton *LRCShow;
    QPushButton *pushButton_BatchDownload;

    void setupUi(QWidget *MusicPlayer)
    {
        if (MusicPlayer->objectName().isEmpty())
            MusicPlayer->setObjectName(QString::fromUtf8("MusicPlayer"));
        MusicPlayer->resize(832, 476);
        MusicPlayer->setStyleSheet(QString::fromUtf8(""));
        label_CurrentTime = new QLabel(MusicPlayer);
        label_CurrentTime->setObjectName(QString::fromUtf8("label_CurrentTime"));
        label_CurrentTime->setGeometry(QRect(390, 390, 41, 21));
        label_CurrentTime->setStyleSheet(QString::fromUtf8(""));
        label_TotalTime = new QLabel(MusicPlayer);
        label_TotalTime->setObjectName(QString::fromUtf8("label_TotalTime"));
        label_TotalTime->setGeometry(QRect(690, 390, 41, 21));
        widget = new QWidget(MusicPlayer);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(450, 100, 331, 211));
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget \n"
"{\n"
"    background-image: url(:/image/LRC_background_image.png);\n"
"    background-attachment: fixed; /* \347\241\256\344\277\235\350\203\214\346\231\257\345\233\276\345\203\217\345\233\272\345\256\232\344\270\215\345\212\250 */\n"
"    background-position: center; /* \345\233\276\345\203\217\345\234\250\346\216\247\344\273\266\344\270\255\345\261\205\344\270\255 */\n"
"    background-repeat: no-repeat; /* \344\270\215\351\207\215\345\244\215\346\230\276\347\244\272\350\203\214\346\231\257\345\233\276\345\203\217 */\n"
"}\n"
"\n"
""));
        label_LRC_1 = new QLabel(widget);
        label_LRC_1->setObjectName(QString::fromUtf8("label_LRC_1"));
        label_LRC_1->setGeometry(QRect(0, 40, 331, 16));
        label_LRC_1->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";\n"
""));
        label_LRC = new QLabel(widget);
        label_LRC->setObjectName(QString::fromUtf8("label_LRC"));
        label_LRC->setGeometry(QRect(0, 10, 331, 16));
        label_LRC->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";\n"
"QLabel#label_LRC \n"
"{\n"
"    border: 0px;\n"
"}\n"
""));
        label_LRC_2 = new QLabel(widget);
        label_LRC_2->setObjectName(QString::fromUtf8("label_LRC_2"));
        label_LRC_2->setGeometry(QRect(0, 70, 331, 16));
        label_LRC_2->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";"));
        label_LRC_3 = new QLabel(widget);
        label_LRC_3->setObjectName(QString::fromUtf8("label_LRC_3"));
        label_LRC_3->setGeometry(QRect(0, 100, 331, 16));
        label_LRC_3->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";"));
        label_LRC_4 = new QLabel(widget);
        label_LRC_4->setObjectName(QString::fromUtf8("label_LRC_4"));
        label_LRC_4->setGeometry(QRect(0, 130, 331, 16));
        label_LRC_4->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";"));
        label_LRC_5 = new QLabel(widget);
        label_LRC_5->setObjectName(QString::fromUtf8("label_LRC_5"));
        label_LRC_5->setGeometry(QRect(0, 160, 331, 16));
        label_LRC_5->setStyleSheet(QString::fromUtf8("font: 9pt \"Blackadder ITC\";"));
        label_LRC_6 = new QLabel(widget);
        label_LRC_6->setObjectName(QString::fromUtf8("label_LRC_6"));
        label_LRC_6->setGeometry(QRect(0, 190, 331, 16));
        horizontalSlider = new QSlider(MusicPlayer);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(390, 410, 321, 20));
        horizontalSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
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
        horizontalSlider->setOrientation(Qt::Horizontal);
        listWidget = new QListWidget(MusicPlayer);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(140, 100, 261, 211));
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget#listWidget \n"
"{\n"
"    border:none;\n"
"    background-image: url(:/image/listWidget_background_image1.png);\n"
"    background-attachment: fixed; /* \347\241\256\344\277\235\350\203\214\346\231\257\345\233\276\345\203\217\345\233\272\345\256\232\344\270\215\345\212\250 */\n"
"    background-position: center; /* \345\233\276\345\203\217\345\234\250\346\216\247\344\273\266\344\270\255\345\261\205\344\270\255 */\n"
"    background-repeat: no-repeat; /* \344\270\215\351\207\215\345\244\215\346\230\276\347\244\272\350\203\214\346\231\257\345\233\276\345\203\217 */\n"
"	font: 9pt \"\345\215\216\346\226\207\351\232\266\344\271\246\";\n"
"	text-decoration: underline;\n"
"}\n"
"	"));
        Play = new QPushButton(MusicPlayer);
        Play->setObjectName(QString::fromUtf8("Play"));
        Play->setGeometry(QRect(540, 430, 31, 31));
        Play->setStyleSheet(QString::fromUtf8("QPushButton \n"
"{\n"
"    background-color: lightgreen;\n"
"    border-radius: 15px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: white; /* \344\275\277\346\226\207\346\234\254\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262\357\274\214\347\241\256\344\277\235\345\234\250\346\267\261\347\273\277\350\211\262\350\203\214\346\231\257\344\270\212\345\217\257\350\247\201 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"QPushButton:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262\357\274\214\345\217\257\344\273\245\346\257\224\346\265\205\347"
                        "\273\277\350\211\262\346\233\264\346\232\227 */\n"
"}\n"
""));
        Next = new QPushButton(MusicPlayer);
        Next->setObjectName(QString::fromUtf8("Next"));
        Next->setGeometry(QRect(580, 430, 31, 31));
        Next->setStyleSheet(QString::fromUtf8("QPushButton \n"
"{\n"
"    background-color: white; /* \345\210\235\345\247\213\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border-radius: 15px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: black; /* \345\210\235\345\247\213\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"    border: 2px solid #90ee90; /* \345\210\235\345\247\213\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton:hover \n"
"{\n"
"    background-color: lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    bord"
                        "er: 2px solid lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: white; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
""));
        Prev = new QPushButton(MusicPlayer);
        Prev->setObjectName(QString::fromUtf8("Prev"));
        Prev->setGeometry(QRect(500, 430, 31, 31));
        Prev->setStyleSheet(QString::fromUtf8("QPushButton \n"
"{\n"
"    background-color: white; /* \345\210\235\345\247\213\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border-radius: 15px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: black; /* \345\210\235\345\247\213\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"    border: 2px solid #90ee90; /* \345\210\235\345\247\213\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton:hover \n"
"{\n"
"    background-color: lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    bord"
                        "er: 2px solid lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: white; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
""));
        verticalSlider = new QSlider(MusicPlayer);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(750, 350, 16, 71));
        verticalSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:vertical \n"
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
        verticalSlider->setOrientation(Qt::Vertical);
        pushButton_volume = new QPushButton(MusicPlayer);
        pushButton_volume->setObjectName(QString::fromUtf8("pushButton_volume"));
        pushButton_volume->setGeometry(QRect(720, 420, 31, 31));
        pushButton_volume->setStyleSheet(QString::fromUtf8("QPushButton \n"
"{\n"
"    border: none;\n"
"    background-color: transparent; /* \346\270\205\351\231\244\351\273\230\350\256\244\350\203\214\346\231\257\350\211\262 */\n"
"    /* width: 70px; /* \350\256\276\347\275\256\346\214\211\351\222\256\345\256\275\345\272\246 */\n"
"    /* height: 70px; /* \350\256\276\347\275\256\346\214\211\351\222\256\351\253\230\345\272\246 */\n"
"    border-radius: 15px; /* \345\234\206\345\275\242\346\214\211\351\222\256\357\274\214\345\215\212\345\276\204\344\270\272\345\256\275\345\272\246\346\210\226\351\253\230\345\272\246\347\232\204\344\270\200\345\215\212 */\n"
"    /* padding: 10px; /* \345\217\257\351\200\211\357\274\232\350\256\276\347\275\256\345\206\205\350\276\271\350\267\235\344\273\245\346\216\247\345\210\266\346\214\211\351\222\256\345\244\247\345\260\217 */\n"
"	border: 2px solid rgb(144, 238, 144); /* \346\267\273\345\212\240\346\265\205\347\273\277\350\211\262\350\276\271\346\241\206 */\n"
"}\n"
"QPushButton::hover\n"
"{\n"
"	background-color: rgb(56, 255, 2"
                        "1);\n"
"};"));
        label_updateVolume = new QLabel(MusicPlayer);
        label_updateVolume->setObjectName(QString::fromUtf8("label_updateVolume"));
        label_updateVolume->setGeometry(QRect(760, 420, 34, 34));
        label_updateVolume->setStyleSheet(QString::fromUtf8("QLabel#label_updateVolume {\n"
"    text-align: center; /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"}\n"
"\n"
""));
        label_baidu = new QLabel(MusicPlayer);
        label_baidu->setObjectName(QString::fromUtf8("label_baidu"));
        label_baidu->setGeometry(QRect(730, 60, 61, 31));
        label_baidu->setStyleSheet(QString::fromUtf8("QLabel#label_baidu \n"
"{\n"
"    border: 2px solid green; /* \350\256\276\347\275\256\347\273\277\350\211\262\350\276\271\346\241\206 */\n"
"    background-color: white; /* \351\273\230\350\256\244\350\203\214\346\231\257\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262 */\n"
"    border-radius: 10px; /* \350\256\276\347\275\256\345\234\206\350\247\222 */\n"
"    padding: 5px 10px; /* \345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QLabel#label_baidu:hover {\n"
"    border-color: lightgreen; /* \346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\344\270\272\346\265\205\347\273\277\350\211\262 */\n"
"    background-color: lightgreen; /* \346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\344\270\272\346\265\205\347\273\277\350\211\262 */\n"
"}\n"
""));
        label_gif_one = new QLabel(MusicPlayer);
        label_gif_one->setObjectName(QString::fromUtf8("label_gif_one"));
        label_gif_one->setGeometry(QRect(730, 10, 101, 51));
        label_gif_one->setStyleSheet(QString::fromUtf8("QLabel#label_gif_one \n"
"{\n"
"    border: 2px solid white; /* \350\256\276\347\275\256\347\231\275\350\211\262\350\276\271\346\241\206 */\n"
"    background-color: white; /* \351\273\230\350\256\244\350\203\214\346\231\257\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262 */\n"
"    border-radius: 5px; /* \350\256\276\347\275\256\345\234\206\350\247\222 */\n"
"    padding: 5px 10px; /* \345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QLabel#label_gif_one:hover {\n"
"    border-color: white; /* \346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\344\270\272\347\231\275\350\211\262 */\n"
"    background-color: lightyellow; /* \346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\344\270\272\346\265\205\351\273\204\350\211\262 */\n"
"}"));
        listWidget_musicposter = new QListWidget(MusicPlayer);
        listWidget_musicposter->setObjectName(QString::fromUtf8("listWidget_musicposter"));
        listWidget_musicposter->setGeometry(QRect(170, 320, 211, 141));
        listWidget_musicposter->setStyleSheet(QString::fromUtf8("QListWidget#listWidget_musicposter\n"
"{\n"
"    background: transparent;\n"
"	border: none;\n"
"}\n"
""));
        pushButton_playmode = new QPushButton(MusicPlayer);
        pushButton_playmode->setObjectName(QString::fromUtf8("pushButton_playmode"));
        pushButton_playmode->setGeometry(QRect(400, 430, 31, 31));
        pushButton_playmode->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_playmode \n"
"{\n"
"    border-radius: 10px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: black; /* \345\210\235\345\247\213\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"    border: 2px solid #90ee90; /* \345\210\235\345\247\213\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#pushButton_playmode:hover \n"
"{\n"
"    background-color: lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201"
                        "\234\346\227\266\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: white; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#pushButton_playmode:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}"));
        pushButton_downloadmusic = new QPushButton(MusicPlayer);
        pushButton_downloadmusic->setObjectName(QString::fromUtf8("pushButton_downloadmusic"));
        pushButton_downloadmusic->setGeometry(QRect(10, 250, 111, 31));
        pushButton_downloadmusic->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_downloadmusic \n"
"{\n"
"    background: transparent;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton#pushButton_downloadmusic:hover \n"
"{\n"
"    background-color: lightgreen;\n"
"}\n"
""));
        showDownloadListButton = new QPushButton(MusicPlayer);
        showDownloadListButton->setObjectName(QString::fromUtf8("showDownloadListButton"));
        showDownloadListButton->setGeometry(QRect(10, 170, 111, 31));
        showDownloadListButton->setStyleSheet(QString::fromUtf8("QPushButton#showDownloadListButton\n"
"{\n"
"    background: transparent;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton#showDownloadListButton:hover \n"
"{\n"
"    background-color: lightgreen;\n"
"}\n"
""));
        showDownloadListPlayButton = new QPushButton(MusicPlayer);
        showDownloadListPlayButton->setObjectName(QString::fromUtf8("showDownloadListPlayButton"));
        showDownloadListPlayButton->setGeometry(QRect(10, 90, 111, 31));
        showDownloadListPlayButton->setStyleSheet(QString::fromUtf8("QPushButton#showDownloadListPlayButton\n"
"{\n"
"    background: transparent;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton#showDownloadListPlayButton:hover \n"
"{\n"
"    background-color: lightgreen;\n"
"}\n"
""));
        label_currentPlayMusicName = new QLabel(MusicPlayer);
        label_currentPlayMusicName->setObjectName(QString::fromUtf8("label_currentPlayMusicName"));
        label_currentPlayMusicName->setGeometry(QRect(450, 380, 221, 20));
        label_currentPlayMusicName->setStyleSheet(QString::fromUtf8(""));
        LRCShow = new QPushButton(MusicPlayer);
        LRCShow->setObjectName(QString::fromUtf8("LRCShow"));
        LRCShow->setGeometry(QRect(660, 430, 31, 31));
        LRCShow->setStyleSheet(QString::fromUtf8("QPushButton#LRCShow \n"
"{\n"
"	border-image: url(:/image/LRCShow.png);\n"
"    background-color: white; /* \345\210\235\345\247\213\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border-radius: 15px; /* \350\260\203\346\225\264\344\270\272\345\220\210\351\200\202\347\232\204\345\200\274\357\274\214\344\275\277\346\214\211\351\222\256\345\217\230\344\270\272\345\234\206\345\275\242 */\n"
"    color: black; /* \345\210\235\345\247\213\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"    padding: 10px; /* \346\267\273\345\212\240\344\270\200\344\272\233\345\241\253\345\205\205\357\274\214\344\273\245\344\275\277\346\214\211\351\222\256\345\205\267\346\234\211\351\200\202\345\275\223\347\232\204\345\244\247\345\260\217 */\n"
"    border: 2px solid #90ee90; /* \345\210\235\345\247\213\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#LRCShow:hover \n"
"{\n"
"    background-color: lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350"
                        "\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid lightgreen; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: white; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QPushButton#LRCShow:pressed \n"
"{\n"
"    background-color: #90ee90; /* \346\214\211\344\270\213\346\227\266\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
""));
        pushButton_BatchDownload = new QPushButton(MusicPlayer);
        pushButton_BatchDownload->setObjectName(QString::fromUtf8("pushButton_BatchDownload"));
        pushButton_BatchDownload->setGeometry(QRect(9, 320, 111, 31));
        pushButton_BatchDownload->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_BatchDownload \n"
"{\n"
"    background: transparent;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton#pushButton_BatchDownload:hover \n"
"{\n"
"    background-color: lightgreen;\n"
"}"));

        retranslateUi(MusicPlayer);

        QMetaObject::connectSlotsByName(MusicPlayer);
    } // setupUi

    void retranslateUi(QWidget *MusicPlayer)
    {
        MusicPlayer->setWindowTitle(QApplication::translate("MusicPlayer", "MusicPlayer", nullptr));
        label_CurrentTime->setText(QApplication::translate("MusicPlayer", "0.0", nullptr));
        label_TotalTime->setText(QApplication::translate("MusicPlayer", "0.0", nullptr));
        label_LRC_1->setText(QString());
        label_LRC->setText(QString());
        label_LRC_2->setText(QString());
        label_LRC_3->setText(QString());
        label_LRC_4->setText(QString());
        label_LRC_5->setText(QString());
        label_LRC_6->setText(QString());
        Play->setText(QString());
        Next->setText(QString());
        Prev->setText(QString());
        pushButton_volume->setText(QString());
        label_updateVolume->setText(QString());
        label_baidu->setText(QString());
        label_gif_one->setText(QString());
        pushButton_playmode->setText(QString());
        pushButton_downloadmusic->setText(QApplication::translate("MusicPlayer", "\344\270\213\350\275\275\346\214\207\345\256\232\346\255\214\346\233\262", nullptr));
        showDownloadListButton->setText(QApplication::translate("MusicPlayer", "\344\270\213\350\275\275\345\210\227\350\241\250\344\277\241\346\201\257", nullptr));
        showDownloadListPlayButton->setText(QApplication::translate("MusicPlayer", "\344\270\213\350\275\275\345\210\227\350\241\250\346\222\255\346\224\276", nullptr));
        label_currentPlayMusicName->setText(QString());
        LRCShow->setText(QString());
        pushButton_BatchDownload->setText(QApplication::translate("MusicPlayer", "\346\211\271\351\207\217\344\270\213\350\275\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MusicPlayer: public Ui_MusicPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICPLAYER_H
