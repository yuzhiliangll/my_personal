#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QTableWidget>
#include <QVBoxLayout>
#include <map>
#include <QTimer>// 定时器
#include "musiclist.h"
#include "rotatewidget.h"
#include "myclientsocket.h"
#include <QBuffer>
#include <QByteArray>

// 20240723--线程池--批量下载__待完成
#include <QRunnable>
#include <QThreadPool>
#include <QJsonDocument>
#include <QJsonObject>
#include "downloadtask.h"


namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QWidget
{
    Q_OBJECT // qt的宏,有这个宏才可以使用信号和槽机制

public:
    explicit MusicPlayer(QWidget *parent = nullptr, MyClientSocket *socket = nullptr); // 构造函数声明
    ~MusicPlayer();

    void InitMusicList();
    // QStringList ReadFromRCFile(const QString& filepath);// 用字符串列表去接
    void AnalysisLRC(const QStringList& LRCList);

    // 20240717--通过歌曲名使用递归来设置海报
    void switchPoster(const QString& musicName);
    QString findPoster(const QString& currentPath, const QString& musicFileName);
    void downloadMusicListIsHidden();// 下载的歌单显示或者隐藏




// 槽函数的声明
public slots:
    void playStateChanged();// 播放状态切换
    void DurationChanged();
    void PositionChanged();// 当前时间位置

    void VolumeWidgetChanged();// 音量
    void VolumeChanged();// 音量大小改变
    void updateVolumeLabel(int value);// 连接滑块数值变化信号
    void ChangedLRC();// 歌词
    void LRCIsShow();// 歌词是否显示
    void resetLRCLabels();// 重置所有歌词标签的样式
    void PlayMusic();
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);// 添加一个槽函数来处理播放结束的信号

    void PlayPrev();// 上一首歌
    void PlayNext();// 下一首歌
    // 播放模式
    void ChangePlayMode();

    // 20240712--待修改
    void handleMusicDataRecv(QByteArray array);
    void DownLoadMusic(const QString& musicName, const QString& artistName, const QString& albumName);// 音乐下载请求

    // 20240718--显示下载列表信息
    void showDownloadList();

    // 20240723输入批量下载列表



private slots:
    void promptForMusicName();//用于显示输入对话框并获取音乐文件名称

    // 20240723--批量下载
    void promptForBatchDownload();// 用于显示输入对话框并获取音乐文件名称
    void handleBatchDownload(const QByteArray &content);
    // 点击事件
    void onBatchDownloadButtonClicked();

private:
    // 发送批量下载请求
    void sendBatchDownloadRequest(const QList<QPair<QString, QPair<QString, QString>>>& musicDataList);

private:
    Ui::MusicPlayer *ui; // ui类的指针
    QMediaPlayer *player;// 媒体播放器指针
    std::map<long long, QString> LRCMap;// 键值对：前面放时间 后面放字符串
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
    void updatePlayModeIcon(); // 更新播放模式图标

    RotateWidget *rw;// 20240704--界面塞进来，让rotatewidget成为它的子对象
    MyClientSocket *CSocket; // 套接字指针

    // 20240717--下载列表信息界面
    bool lrcIsVisible = false; // 默认为隐藏歌词
    QWidget *downloadListWidget;// 使用这个作为容器可以让你在设计和管理UI界面时更加灵活(也可以不使用)
    QVBoxLayout *mainLayout;// 用于添加到主布局
    QTableWidget *downloadTable;

private:
    // 20240718--设置界面以及列表
    void setupDownloadUI();// 设置下载列表信息界面
    void setupDownloadList();//用于填充下载列表信息

private:
    // 20240723--关于批量下载
    QThreadPool *threadPool;// 添加线程池成员变量

};
/***********************************************************************************/
//20240723需要实现一个继承自 QRunnable 的类来处理批量下载任务--见downloadtask文件





#endif // MUSICPLAYER_H
