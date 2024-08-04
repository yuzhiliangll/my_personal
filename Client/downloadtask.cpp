#include "downloadtask.h"
#include "myclientsocket.h"

DownloadTask::DownloadTask(const QJsonArray &musicArray, MyClientSocket *socket)
    : musicArray(musicArray), socket(socket)//初始化列表中将参数赋值给类成员变量 musicArray 和 socket
{

}


void DownloadTask::run()// 任务的主逻辑,用于发送批量下载请求
{
    // 包括两个字段: 请求类型和音乐列表
    QJsonObject jsonObj;
    jsonObj["request"] = "BatchDownloadMusic";
    jsonObj["MusicList"] = musicArray;// 需要下载的音乐列表

    QByteArray content = QJsonDocument(jsonObj).toJson();
    size_t size = static_cast<size_t>(content.size());
    content.insert(0, reinterpret_cast<const char*>(&size), sizeof(size_t));//将内容大小（size）插入到 QByteArray 的开头

    emit downloadCompleted(content);//发射信号，通知下载完成，并传递内容
}

