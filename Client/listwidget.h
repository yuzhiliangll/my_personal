#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include "myclientsocket.h" // 假设你的套接字类在这里声明
#include <QMediaPlayer>
#include <QTableWidget>
#include <QVBoxLayout>
#include <map>
#include <QTimer>// 定时器
#include "musiclist.h"
#include "rotatewidget.h"
#include <QBuffer>
#include <QByteArray>
#include <QTableWidgetItem>



namespace Ui {
class ListWidget;
}

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = nullptr, MyClientSocket *socket = nullptr); // 增加套接字参数
    ~ListWidget();

    // void InitOnlineMusicList();
    void AnalysisOnlineMusicLRC(const QStringList& LRCList);


    // 20240719--获取用户名
    void setUsername(const QString &account);
    QString getUsername() const;
    // 20240720--在线音乐播放请求
    void onlinePlayMusic(const QString& musicName, const QString& artistName, const QString& albumName);
    // 20240721--在线音乐海报切换
    QString getAlbumPoster(const QString& albumName);

    // 20240722__添加到我喜欢的列表请求
    void myLikeMusicClicked();
    void addToMyLikeMusicList(const QString &songName, const QString &singer, const QString &album);



signals:




public slots:
    void OnlineplayStateChanged();// 播放状态切换
    void OnlineDurationChanged();
    void OnlinePositionChanged();// 当前时间位置

    void OnlineVolumeWidgetChanged();// 音量
    void OnlineVolumeChanged();// 音量大小改变
    void OnlineupdateVolumeLabel(int value);// 连接滑块数值变化信号
    void OnlineChangedLRC();// 歌词
    void OnlineLRCIsShow();// 歌词是否显示
    void OnlineresetLRCLabels();// 重置所有歌词标签的样式
    //void OnlinePlayMusic();
    void OnlinemediaStatusChanged(QMediaPlayer::MediaStatus status);// 添加一个槽函数来处理播放结束的信号

    void OnlinePlayPrev();// 上一首歌
    void OnlinePlayNext();// 下一首歌

    // 播放模式
    void OnlineChangePlayMode();

    // 20240712--待修改
    void OnlinehandleMusicDataRecv(QByteArray array);

    // 20240719--[增加]
    void onlineMusicListenClicked();// 在线听歌按钮点击处理
    void onTableCellDoubleClicked(int row, int column);// 处理行双击事件

    // 20240721__我喜欢的列表
    void loadFavorites();// 加载我喜欢的
    // 20240722__发送我喜欢请求
    void sendFavoriteUpdateRequest(const QString &songName, const QString &singer, const QString &album, bool add);


private slots:


private:
    Ui::ListWidget *ui;
    MyClientSocket *CSocket; // 套接字成员变量
    QMediaPlayer *player;// 媒体播放器指针
    std::map<long long, QString> LRCMap;// 键值对：前面放时间 后面放字符串__用于歌词时间和内容的映射
    QTimer timer;

    MusicList *ml;// 音乐歌单---指针
    std::map<QString, QUrl> MusicListInfo;// 音乐列表信息

    enum PlayMode// 添加枚举类型 PlayMode 和变量 currentPlayMode
    {
        ListLoop,
        Random,
        Sequential,
        SingleLoop
    };
    PlayMode currentPlayMode;// 存储当前的播放模式
    void OnlineupdatePlayModeIcon(); // 更新播放模式图标

    RotateWidget *rw;// 20240704--界面塞进来，让rotatewidget成为它的子对象

    // 20240719--存储用户名
    QString username;
    // 20240720--音乐缓存区
    QByteArray musicBufferData;// 音乐mp3数据缓冲区
    QBuffer *musicBuffer;// QBuffer 对象
    QString currentMusicName;   // 当前播放的音乐名称
    qint64 totalSize; // 添加这个变量来保存当前音乐的总大小
    // 20240721__[新增]_用于存储多个海报文件的数据缓冲区
    QMap<QString, QByteArray> posterDataMap; // 存储海报文件数据的缓冲区_QString类型 代表文件名,QByteArray类型代表文件的二进制数据
    // ----
    QByteArray lyricsBufferData; // 定义歌词文件数据的缓冲区
    QMap<qint64, QString> lyricsMap; // 20240721__好像没有用到__存储时间戳和对应的歌词文本


};

#endif // LISTWIDGET_H
