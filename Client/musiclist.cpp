#include "musiclist.h"
#include <QDir>
#include <QDebug>
#include <QUrl>
#include <QDirIterator>


MusicList::MusicList(QObject *parent) : QObject(parent)
{

}


// 初始化
LocalMusicList::LocalMusicList(QObject *parent): MusicList(parent)
{

}

// 返回包含音乐文件名和对应歌词文件名
std::map<QString, QUrl> LocalMusicList::GetMusicList()
{
    QDir dir("D:\\QT259\\Client\\DownloadMusic");
    if(dir.exists() == false)
    {
        qDebug()<< "音乐文件夹路径不存在" << endl;
        return {};// 返回 空
    }

    // 开始读文件夹下的文件
    std::map<QString, QUrl> m;
    // 20240715--修改:获取某个目录下指定的所有文件，包括子目录中的文件，可以使用 QDirIterator 类
    QDirIterator it(dir.path(), QStringList() << "*.mp3" << "*.lrc", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
       it.next();
       QFileInfo fileInfo = it.fileInfo();
       if (fileInfo.suffix() == "mp3")
       {
           // baseName:不带后缀的 纯文件名
           // absoluteFilePath：绝对文件路径
           m.insert({fileInfo.baseName(), QUrl::fromLocalFile(fileInfo.absoluteFilePath())});
       }
       else if (fileInfo.suffix() == "lrc")
       {
           LRCMap.insert({fileInfo.baseName(), fileInfo.absoluteFilePath()});
       }
    }
    return m;
}

// 从 LRCMap 中根据音乐文件名查找对应的歌词文件，并读取其内容到一个 QStringList 中
QStringList LocalMusicList::GetLRC(const QString &MusicName)
{
    auto ite = LRCMap.find(MusicName);// 通过 LRCMap.find(MusicName) 在 LRCMap 中查找键为 MusicName 的条目
    if(ite == LRCMap.end())// 不存在空的 QStringLists
    {
        return {};
    }

    QFile file(ite->second);// 用 ite->second（即 LRCMap[MusicName]）作为文件路径构造文件对象
    QStringList list; // QString 默认使用 UTF-16 编码内部表示，但文件读取通常为 UTF-8
    if (file.open(QIODevice::ReadOnly))// 打开文件，确保文件以文本模式读取
    {
        QTextStream text(&file);// 文本流对象：只读文本 清掉\r \n
        while (text.atEnd() == false)
        {
            // 读取一行，并将其转换为QString后插入到list中
            list.push_back(text.readLine()); // 去掉换行符和空白字符
        }
        file.close();
    }
    else
    {
        return {};
    }
    return list;
}



