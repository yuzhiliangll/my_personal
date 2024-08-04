#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QObject>
#include <map>

class MusicList : public QObject
{
    Q_OBJECT
public:
    explicit MusicList(QObject *parent = nullptr);
    virtual std::map<QString, QUrl> GetMusicList() = 0; // 纯虚---获得音乐列表
    virtual QStringList GetLRC(const QString& MusicName) = 0;// 获得 音乐名对应的歌词


signals:

public slots:
};

// 本地文件
class LocalMusicList:public MusicList
{
    Q_OBJECT
public:
    explicit LocalMusicList(QObject *parent = nullptr);
    virtual std::map<QString, QUrl> GetMusicList();
    virtual QStringList GetLRC(const QString& MusicName);

private:
    std::map<QString, QString> LRCMap;
};

#endif // MUSICLIST_H
