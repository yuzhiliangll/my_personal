#include "listwidget.h"
#include "ui_listwidget.h"
#include <QIcon>        // 用于处理图标的类
#include <QUrl>         // 类提供了对 URL 的解析、构建和操作功能
#include <QFile>
#include <QDebug>       // 代替 std::cout
#include <QPalette>     // 用于图像和颜色处理的类库。
#include <QBrush>
#include <QPixmap>
#include <QMouseEvent>  // 添加鼠标事件头文件
#include <QFileDialog>  // 文件对话框
#include <QDir>         // 操作文件的类
#include <QMovie>       // 可以使用动态图
#include <QHBoxLayout>  // 布局类
#include <QBuffer>      // 缓冲区
#include <QMessageBox>  // 提示框
#include <QInputDialog>
#include <QHeaderView>
#include <QDomDocument>
#include <QDomNodeList>
#include <QTableWidget>



ListWidget::ListWidget(QWidget *parent, MyClientSocket *socket) :
    QWidget(parent),
    ui(new Ui::ListWidget),
    CSocket(socket), // 初始化套接字成员变量
    currentPlayMode(ListLoop) // 初始化播放模式
{
    ui->setupUi(this);
    ui->widget->hide(); // 确保一开始显示歌词控件隐藏
    // 设置 QPalette 和 QBrush 来设置背景图片
    {
        QPalette palette;
        QPixmap backgroundPixmap(":/image/background_image.png"); // 确保图片在资源文件中
        palette.setBrush(QPalette::Window, QBrush(backgroundPixmap));
        this->setPalette(palette);

        // 确保窗口的自动填充背景属性为真
        this->setAutoFillBackground(true);
    }

    player = new QMediaPlayer;// 媒体播放对象
    // ml = new LocalMusicList();// 文件列表--用的是多态

    // 20240704--海报旋转以写死--待实现对应海报的切换
    // 设置旋转小部件
    ui->Onlinemusicposter->setFixedSize(200, 180);  // 设置合适的固定尺寸
    // 手动布局
    this->rw = new RotateWidget;
    rw->SetPixMap(QPixmap(R"(D:\QT259\Client\image\LRC_background_image.png)"));
    QHBoxLayout * layout = new  QHBoxLayout;
    layout->addWidget(rw);// 塞进去
    ui->Onlinemusicposter->setLayout(layout);

    // 设置界面标题
    this->setWindowTitle("Music player");

    // 设置窗口图标
    this->setWindowIcon(QIcon(":/image/logo.png"));
    // 设置窗口透明度
    this->setWindowOpacity(0.93); // 透明度值范围为 0.0 (完全透明) 到 1.0 (不透明)
    // 创建QMovie对象并设置GIF动画
    QMovie *movie = new QMovie(":/image/gif_one.gif");
    // 设置QMovie到QLabel中显示动画
    ui->label_gif->setMovie(movie);
    // 开始播放动画
    movie->start();
    // 设置QLabel适应内容大小
    ui->label_gif->setScaledContents(true);

    ui->OnlinePlay->setIcon(QIcon(":/image/Play.png"));
    ui->OnlinePrev->setIcon(QIcon(":/image/Prev.png"));
    ui->OnlineNext->setIcon(QIcon(":/image/Next.png"));
    ui->OnlinepushButton_volume->setIcon(QIcon(":/image/volume.png"));// 音量

    // 设置百度超链接文本和样式
    ui->Onlinebaidu->setText("<a href=\"https://www.baidu.com\" style=\"font-family: 'Bauhaus 93'; font-size: 14px;\">百度</a>");
    ui->Onlinebaidu->setOpenExternalLinks(true);

    // 更新播放 默认是列表模式
    OnlineupdatePlayModeIcon();

    // 信号 和 槽 机制 ： 其底层原理就是回调机制
    // connect(信号的发出者  , 信号(函数)  ,  信号的接收者 , 槽函数(做出响应的函数));
    connect(ui->OnlinePlay, &QPushButton::clicked, this, &ListWidget::OnlineplayStateChanged);
    connect(ui->OnlinepushButton_volume, &QPushButton::clicked, this, &ListWidget::OnlineVolumeWidgetChanged);
    // 上一首歌
    connect(ui->OnlinePrev, &QPushButton::clicked, this, &ListWidget::OnlinePlayPrev);
    // 下一首歌
    connect(ui->OnlineNext, &QPushButton::clicked, this, &ListWidget::OnlinePlayNext);

    // 播放
    connect(player, &QMediaPlayer::durationChanged, this, &ListWidget::OnlineDurationChanged);
    // 当前播放的进度
    connect(player, &QMediaPlayer::positionChanged, this, &ListWidget::OnlinePositionChanged);
    // 在构造函数中连接播放结束信号
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &ListWidget::OnlinemediaStatusChanged);

    // 滑轨拖动，让音乐播放的进度改变
    connect(ui->OnlinehorizontalSlider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(ui->OnlineverticalSlider, &QSlider::sliderMoved, this, &ListWidget::OnlineVolumeChanged);// 音量修改
    connect(ui->OnlineverticalSlider, &QSlider::valueChanged, this, &ListWidget::OnlineVolumeChanged);
    // 连接滑块数值变化信号
    connect(ui->OnlineverticalSlider, &QSlider::valueChanged, this, &ListWidget::OnlineupdateVolumeLabel);
    ui->OnlineverticalSlider->setRange(0, 100);
    // 初始值设置
    ui->OnlineverticalSlider->setValue(100);
    // 音量按之前 隐藏
    ui->OnlineverticalSlider->hide();
    // 设置音量更新标签的初始值
    ui->Onlinelabel_updateVolume->setText(QString::number(ui->OnlineverticalSlider->value()));
    // 定时器设置
    timer.setInterval(500);// // 设置一个较短的定时器间隔---检查一次
    // 歌词显示(timer 是一个指针)
    connect(&timer, &QTimer::timeout, this, &ListWidget::OnlineChangedLRC);
    connect(ui->OnlineLRCShow, &QPushButton::clicked, this, &ListWidget::OnlineLRCIsShow);// 20240720--歌词是否显示

    // 双击音乐列表
    // 20240719--设置在线播放按钮
    // 播放列表构造函数中初始化
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "歌曲" << "歌手" << "专辑");
    ui->tableWidget->hide(); // 默认隐藏
    connect(ui->onlineMusicPlay, &QPushButton::clicked, this, &ListWidget::onlineMusicListenClicked);
    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, &ListWidget::onTableCellDoubleClicked);//处理双击事件

    // 接收数据时处理
    connect(CSocket, &MyClientSocket::DataRecv, this, &ListWidget::OnlinehandleMusicDataRecv); // 连接信号到槽

    // 20240720--缓存区初始化
    musicBuffer = new QBuffer(this);
    currentMusicName = "";

    // 20240721
    connect(ui->pushButton_myLikeMusicList, &QPushButton::clicked, this, &ListWidget::loadFavorites);
    // 20240722--我喜欢点击
    connect(ui->pushButton_myLikeMusic, &QPushButton::clicked, this, &ListWidget::myLikeMusicClicked);
    ui->pushButton_myLikeMusic->setIcon(QIcon(":/image/heart.png"));

    // 切换__播放模式
    connect(ui->OnlinepushButton_playmode, &QPushButton::clicked, this, &ListWidget::OnlineChangePlayMode);


}

ListWidget::~ListWidget()
{
    delete ui;
}

// 20240719--获取用户名
void ListWidget::setUsername(const QString &account)
{
    username = account;
}

QString ListWidget::getUsername() const
{
    return username;
}

long OnlineGetMusicTime(QString& str)
{
    str.remove(0, 1);// // 删除开头的 '['

    auto minute = str.split(":")[0].toInt();
    auto msecond = str.split(".")[1].toInt();
    auto second = str.split(":")[1].split(".")[0].toInt();

    return minute * 60 * 1000 + second * 1000 + msecond;
}

// 歌词解析
void ListWidget::AnalysisOnlineMusicLRC(const QStringList &LRCList)
{
    LRCMap.clear();// 清空
    for(auto ite = LRCList.begin(); ite != LRCList.end(); ite++)
    {
        auto InfoList = ite->split("]");
        if(InfoList.size() != 2)
        {
            continue;// 过滤
        }
        LRCMap.insert({OnlineGetMusicTime(InfoList[0]), InfoList[1]});
    }
}

// 播放状态
void ListWidget::OnlineplayStateChanged()
{
    qDebug() << "OnlineplayStateChanged called"; // 添加调试信息
    // 判断是否正在播放
    if(player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();// 暂停
        rw->Stop();
        ui->OnlinePlay->setIcon(QIcon(":/image/Play.png"));
        timer.stop();
    }
    else
    {
        player->play();// 播放
        rw->Start();
        ui->OnlinePlay->setIcon(QIcon(":/image/Pause.png"));
        timer.start();// 启动定时器
    }
}

// 更新总时长
void ListWidget::OnlineDurationChanged()
{
    qint64 duration = player->duration();// 使用 qint64 类型来存储持续时间，确保足够大的范围
    // 将这个数值转换为QString类型
    QString timeStr = QString::number(duration / 1000 / 60)// 计算分钟
            + ":"
            + QString::number(duration / 1000 % 60);       // 计算秒钟
    ui->Onlinelabel_TotalTime->setText(timeStr);
    // 总长度 给到滑轨
    ui->OnlinehorizontalSlider->setRange(0, static_cast<int>(duration));// 将 qint64 类型转换为 int 类型
}

// 更新当前播放位置
void ListWidget::OnlinePositionChanged()
{
    qint64 pos = player->position();// 使用 qint64 类型来存储当前播放位置
    QString timeStr = QString::number(pos / 1000 / 60)
                        + ":"
                        + QString::number(pos / 1000 % 60);
    ui->Onlinelabel_CurrentTime->setText(timeStr);
    // 滑轨定位
    ui->OnlinehorizontalSlider->setValue(static_cast<int>(pos));
}

void ListWidget::OnlineVolumeWidgetChanged()
{
    // 按之前隐藏
    if (ui->OnlineverticalSlider->isHidden())
    {
        // 按一下显示
        ui->OnlineverticalSlider->show();
    }
    else
    {
        ui->OnlineverticalSlider->hide();
    }
}

// 音量修改 + 对应图标显示
void ListWidget::OnlineVolumeChanged()
{
    int volume = ui->OnlineverticalSlider->value();
    player->setVolume(volume);

    // 如果滑块的值为0，表示音量被调整到最低
    if (volume == 0)
    {
        // 可以在这里添加额外的操作，比如静音图标等
        ui->OnlinepushButton_volume->setIcon(QIcon(":/image/Muted.png"));// 静音
    }
    else if (volume <= 60)
    {
        ui->OnlinepushButton_volume->setIcon(QIcon(":/image/VolumeLow.png")); // 低音量图标
    }
    else
    {
        ui->OnlinepushButton_volume->setIcon(QIcon(":/image/VolumeHigh.png")); // 高音量图标
    }

}

// 更新音量数值显示
void ListWidget::OnlineupdateVolumeLabel(int value)
{
    ui->Onlinelabel_updateVolume->setText(QString::number(value));
}

// 对应的播放时间->显示歌词
void ListWidget::OnlineChangedLRC()
{
    long long time = player->position();// 先获取当前播放时间
    // 特殊情况
    // 如果歌词列表 LRCMap 为空，或者当前时间比歌词的最早时间还早，则直接返回，不做任何处理
    if(LRCMap.size() == 0 || time < LRCMap.begin()->first)
    {
        return;
    }

    // 找到当前时间对应的歌词行
    auto currentLine = LRCMap.upper_bound(time);// upper_bound 函数返回一个迭代器，指向第一个大于 time 的键值对的位置
    if (currentLine != LRCMap.begin())
    {
        if (currentLine == LRCMap.end() || currentLine->first > time)
        {
            --currentLine;// 向前移一个迭代器---确保它对应的的歌词是 当前时间的歌词
        }
    }

    // 创建一个容器来保存上下歌词
    QStringList lrcTexts;
    // 向下获取 7 行歌词
    auto endIter = currentLine;
    for (int i = 0; i < 7 && endIter != LRCMap.end(); ++i)// 考虑到可能会超出 LRCMap 的边界
    {
        ++endIter;
    }

    // 像容器中添加歌词
    lrcTexts.clear();
    for(auto iter = currentLine; iter != endIter; iter++)
    {
        lrcTexts << iter->second;
    }

    // 更新 QLabel 的文本和颜色
    QLabel* labels[] = {ui->OnlineLRC, ui->OnlineLRC_1, ui->OnlineLRC_2, ui->OnlineLRC_3, ui->OnlineLRC_4, ui->OnlineLRC_5, ui->OnlineLRC_6};

    for (int i = 0; i < 7; ++i)
    {
        if (i < lrcTexts.size())
        {
            // 如果 i 小于 lrcTexts 的大小，则更新第 i 个 QLabel 的文本
            labels[i]->setText(lrcTexts[i]);
            // 如果是当前行，设置背景为红色，文本为白色
            if (lrcTexts[i] == currentLine->second)
            {
                labels[i]->setStyleSheet("color: red;");
            }
            else
            {
                labels[i]->setStyleSheet("color: purple;");
            }
        }
        else
        {
            // 如果 i 大于等于 lrcTexts 的大小，则清除第 i 个 QLabel 的文本
            labels[i]->clear();
        }
    }
}
// 歌词是否显示
void ListWidget::OnlineLRCIsShow()
{
    if(ui->widget->isVisible())
    {
        ui->widget->hide();
    }
    else
    {
        ui->widget->show();
    }
}
// 重置所有歌词标签的样式
void ListWidget::OnlineresetLRCLabels()
{
    QLabel* labels[] = {ui->OnlineLRC, ui->OnlineLRC_1, ui->OnlineLRC_2, ui->OnlineLRC_3, ui->OnlineLRC_4, ui->OnlineLRC_5, ui->OnlineLRC_6};
    for (int i = 0; i < 7; ++i)
    {
        labels[i]->setText("");
        labels[i]->setStyleSheet("");
    }
}


// 播放结束信号处理槽函数
// 信号且状态为 QMediaPlayer::EndOfMedia 时，自动切换到下一首歌曲
void ListWidget::OnlinemediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
       OnlinePlayNext();
    }
}

void ListWidget::OnlinePlayPrev()
{
    // 增加模式选择后进行修改
    // 列表中获取当前选中的位置
    int currentIndex = ui->tableWidget->currentRow();
    int rowCount = ui->tableWidget->rowCount();//获取 tableWidget 中行的总数，存储在 rowCount 中

    switch (currentPlayMode)
    {
    case ListLoop:
    case Sequential:// 计算上一首歌的索引
        // 计算上一首歌的索引。如果当前索引减1后是负数，通过加上 rowCount 并取模来确保索引在范围内，使其循环到列表末尾
        currentIndex = (currentIndex - 1 + rowCount) % rowCount;
        break;
    case Random:
        // 随机选择列表中的一首歌
        currentIndex = qrand() % rowCount;
        break;
    case SingleLoop:
        // 单曲循环不改变 currentIndex
        break;
    }
    // 20240722--待修改
    // 确保 currentIndex 在有效范围内
    if (currentIndex >= 0 && currentIndex < rowCount)
    {
        ui->tableWidget->selectRow(currentIndex);
        QString musicName = ui->tableWidget->item(currentIndex, 0)->text();
        QString artistName = ui->tableWidget->item(currentIndex, 1)->text();
        QString albumName = ui->tableWidget->item(currentIndex, 2)->text();
        ui->label_currentPlayMusic->setText(musicName);// 更新
        onlinePlayMusic(musicName, artistName, albumName);
        OnlineresetLRCLabels();
    }
    else
    {
        qWarning() << "Invalid index: " << currentIndex;
    }
}

void ListWidget::OnlinePlayNext()
{
    // 列表中获取当前选中的位置
    int currentIndex = ui->tableWidget->currentRow();
    int rowCount = ui->tableWidget->rowCount();

    switch (currentPlayMode)
    {
    case ListLoop:// 计算下一首歌的索引
        // 计算下一首歌的索引，模运算确保索引在范围内
        currentIndex = (currentIndex + 1) % rowCount;
        break;
    case Sequential:
        currentIndex = (currentIndex + 1);
        if (currentIndex >= rowCount)
        {
            currentIndex = 0; // 到达列表末尾，则循环到列表的开头
        }
        break;
    case Random:
        // 随机选择列表中的一首歌
        currentIndex = qrand() % rowCount;
        break;
    case SingleLoop:
        // 单曲循环不改变 currentIndex
        break;
    }
    // 20240722--下面待修改
    // 确保 currentIndex 在有效范围内
    if (currentIndex >= 0 && currentIndex < rowCount)
    {
        ui->tableWidget->selectRow(currentIndex);
        QString musicName = ui->tableWidget->item(currentIndex, 0)->text();
        QString artistName = ui->tableWidget->item(currentIndex, 1)->text();
        QString albumName = ui->tableWidget->item(currentIndex, 2)->text();
        ui->label_currentPlayMusic->setText(musicName);// 更新
        onlinePlayMusic(musicName, artistName, albumName);
        OnlineresetLRCLabels();
    }
    else
    {
        qWarning() << "Invalid index: " << currentIndex;
    }
}


// 切换播放模式
void ListWidget::OnlineChangePlayMode()
{
    qDebug() << "Current play mode: " << currentPlayMode;  // 调试输出当前播放模式
    switch (currentPlayMode)
    {
    case Sequential:// 如果当前模式为Sequential, 则切换到ListLoop模式
        currentPlayMode = ListLoop;
        break;
    case ListLoop:
        currentPlayMode = SingleLoop;
        break;
    case SingleLoop:
        currentPlayMode = Random;
        break;
    case Random:
        currentPlayMode = Sequential;
        break;
    }

    OnlineupdatePlayModeIcon();
}

// 更新播放模式图标
void ListWidget::OnlineupdatePlayModeIcon()
{
    switch (currentPlayMode)
    {
    case Sequential:
        ui->OnlinepushButton_playmode->setIcon(QIcon(":/image/Sequentialplay.png"));
        break;
    case ListLoop:
        ui->OnlinepushButton_playmode->setIcon(QIcon(":/image/ListMode.png"));
        break;
    case SingleLoop:
        ui->OnlinepushButton_playmode->setIcon(QIcon(":/image/Singlecycle.png"));
        break;
    case Random:
        ui->OnlinepushButton_playmode->setIcon(QIcon(":/image/Shuffleplay.png"));
        break;
    }
}
/*****************************************************************************************/
// 定义一个常量，表示播放的阈值（可以根据实际需求调整）
// 20240723__关于缓冲达到阈值播放,吕老师说必须把时间传过去,才能进行进度条完全的显示
// const qint64 PLAYBACK_THRESHOLD = 512 * 1024; // 512KB
void ListWidget::OnlinehandleMusicDataRecv(QByteArray array)// -----
{
    // -------处理接受的数据
    // 音乐文件下载或者 20240720--在线播放数据
    auto rootObj = QJsonDocument::fromJson(array).object();// 将接收到的字节数组转换为 QJsonDocument 对象
    QString status = rootObj["status"].toString();
    QString fileName = rootObj["FileName"].toString();// 获取文件名
    QString artistName = rootObj["ArtistName"].toString(); // 获取歌手名
    QString albumName = rootObj["AlbumName"].toString(); // 获取专辑名
    if (status == "OnlinePlay")
    {
        QString basePath = "../Client/Cache/";
        QString filePath = basePath + fileName;
        QString fileExtension = QFileInfo(fileName).suffix(); // 获取文件扩展名

        if (rootObj["request"].toString() == "OnlinePlayMusic")
        {
            // 将数据写入缓冲区
            QByteArray data = QByteArray::fromHex(rootObj["data"].toString().toUtf8());
            totalSize = rootObj["TotalSize"].toInt();// 更新 totalSize
            // qDebug()<< "totalSize = " << totalSize;
            int readSize = rootObj["ReadSize"].toInt();

            if (fileExtension == "mp3")
            {
                if (fileName != currentMusicName)
                {
                    musicBufferData.clear();
                    currentMusicName = fileName;
                    player->stop();
                    musicBuffer->close();
                    musicBufferData.clear(); // 确保清空旧数据
                }

                if (fileName == currentMusicName && musicBufferData.size() >= totalSize)
                {
                    return;
                }

                musicBufferData.append(data);
                musicBuffer->setData(musicBufferData);

                // 播放条件：只要缓存数据量达到阈值就开始播放且播放器不在播放状态
                if (readSize >= totalSize)// musicBufferData.size() >= PLAYBACK_THRESHOLD
                {
                    if (player->state() != QMediaPlayer::PlayingState)
                    {
                        // 先切换海报
                        QString posterPath = getAlbumPoster(albumName); // 获取专辑海报路径
                        if (!posterPath.isEmpty())
                        {
                            // 使用获取的路径设置海报
                            rw->SetPixMap(QPixmap(posterPath));
                        }
                        else
                        {
                            // 使用默认海报
                            rw->SetPixMap(QPixmap(R"(D:\QT259\Client\image\LRC_background_image.png)"));
                        }

                        musicBuffer->open(QIODevice::ReadOnly);
                        player->setMedia(QMediaContent(), musicBuffer);

                        //20240722-- 更新播放状态图标
                        ui->OnlinePlay->setIcon(QIcon(":/image/Pause.png"));
                        player->play();

                    }
                }
                if (readSize < totalSize)
                {
                    return;
                }
                else
                {
                    musicBuffer->seek(musicBuffer->size());//将 musicBuffer 的文件指针移动到缓冲区数据的末尾位置__常用于在继续向缓冲区追加数据时确保新的数据不会覆盖旧的数据，而是追加在缓冲区的末尾
                }
            }
            // 歌词
            if (fileExtension == "lrc")
            {
                // 处理歌词文件
                QByteArray Lyricsdata = QByteArray::fromHex(rootObj["Lyricsdata"].toString().toUtf8());

                // 将歌词数据追加到缓冲区
                if (fileName != currentMusicName)
                {
                    lyricsBufferData.clear();
                    currentMusicName = fileName;
                }
                lyricsBufferData.append(Lyricsdata);

                // 处理歌词数据
                QString lyricsText = QString::fromLocal8Bit(lyricsBufferData);//可以尝试使用 QString::fromLocal8Bit() 方法进行转换，这是一个常见的中国本地编码（GBK）
                qDebug() << "Parsed lyrics text:" << lyricsText; // 检查歌词文本是否正确
                // 解析歌词__第二个选项是忽略并跳过任何空的部分，这意味着结果列表中不会包含空字符串
                QStringList LRCList = lyricsText.split("\n", QString::SkipEmptyParts);// 按照换行符 "\n" 分割成多个子字符串，并存储在一个 QStringList 列表中
                AnalysisOnlineMusicLRC(LRCList);
//                QFile file(filePath);
//                if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
//                {
//                    qDebug() << "Cannot open file for writing:" << file.errorString();
//                    return;
//                }
//                file.write(Lyricsdata);
//                file.close();
            }
            // 海报
            if (fileExtension == "png")
            {
                // 处理海报文件
                QByteArray Posterdata = QByteArray::fromHex(rootObj["Posterdata"].toString().toUtf8());
                // 如果 posterDataMap 中没有这个文件的数据，初始化一个新的 QByteArray
                if (!posterDataMap.contains(fileName))
                {
                    posterDataMap[fileName] = QByteArray();
                }
                // 将接收到的数据追加到对应的 QByteArray 中
                posterDataMap[fileName].append(Posterdata);
                // 检查数据是否完整
                qint64 expectedSize = rootObj["TotalposterSize"].toInt();
                if (posterDataMap[fileName].size() >= expectedSize)
                {
                    // 数据完整，写入文件
                    QFile file("../Client/Cache/" + fileName);
                    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    {
                        qDebug() << "Cannot open file for writing:" << file.errorString();
                        return;
                    }
                    file.write(posterDataMap[fileName]);
                    file.close();
                    // 清除已处理的数据
                    posterDataMap.remove(fileName);
                }
            }
            // 音乐列表
            if (fileExtension == "xml")
            {
                // 处理音乐列表文件
                QByteArray MusicListData = QByteArray::fromHex(rootObj["MusicListData"].toString().toUtf8());
                QFile file(basePath + fileName);
                if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                {
                    qDebug() << "Cannot open file for writing:" << file.errorString();
                    return;
                }
                file.write(MusicListData);
                file.close();
                // 处理完成后，可以解析并显示音乐列表
            }
        }
    }
    else if(status == "AddToFavorites" || status == "RemoveFromFavorites")
    {
        QString response = rootObj["response"].toString();
        int result = rootObj["result"].toInt();
        if (result == 1)
        {
            if(status == "AddToFavorites")
            {
                qDebug() << "添加到我喜欢列表成功：" << response;
                // 执行相关的逻辑，例如更新UI
            }
            else if(status == "RemoveFromFavorites")
            {
                qDebug() << "从我喜欢列表删除成功：" << response;
                // 执行相关的逻辑，例如更新UI
            }
        }
    }
}
// 20240719--[增加]
void ListWidget::onlineMusicListenClicked()
{
    // 切换界面的显示状态
    if (ui->tableWidget->isVisible())
    {
        ui->tableWidget->hide();
    }
    else
    {
        ui->tableWidget->show();
        // 清空表格
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);

        // 打开 XML 文件
        QFile file("D:/QT259/Client/Cache/MusicListInfo.xml");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning() << "无法打开 XML 文件";
            return;
        }
        /*读出xml内容*/
        auto Content = file.readAll();
        file.close();
        QString errorMsg;
        int line, column;
        QDomDocument doc;
        if (doc.setContent(Content, &errorMsg, &line, &column) == false)  //doc.setContent()  从文本中读取数据并进行解析
        {
             qDebug()<<"line : "<<line<<" column : "<<column<<" msg : "<<errorMsg<<endl;
             return;
        }
        qDebug()<<"xml解析成功!\n";
        QDomElement root = doc.documentElement();// 获取xml根元素
        QDomNodeList songNodes = root.elementsByTagName("歌曲");//获取根元素下所有名为 歌曲 的子节点
        // 填充表格
        for (int i = 0; i < songNodes.count(); ++i)
        {
            QDomNode songNode = songNodes.at(i);
            if (songNode.isElement())
            {
                QDomElement songElement = songNode.toElement();
                QString name = songElement.attribute("名称");
                QString singer = songElement.attribute("歌手");
                QString album = songElement.attribute("专辑");
                // 创建只读项
                QTableWidgetItem *nameItem = new QTableWidgetItem(name);
                QTableWidgetItem *singerItem = new QTableWidgetItem(singer);
                QTableWidgetItem *albumItem = new QTableWidgetItem(album);
                // 设置项为只读
                nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
                singerItem->setFlags(singerItem->flags() & ~Qt::ItemIsEditable);
                albumItem->setFlags(albumItem->flags() & ~Qt::ItemIsEditable);
                // 添加一行到表格
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                ui->tableWidget->setItem(row, 0, nameItem);
                ui->tableWidget->setItem(row, 1, singerItem);
                ui->tableWidget->setItem(row, 2, albumItem);
                qDebug() << "名称: " << name << ", 歌手: " << singer << ", 专辑: " << album;
            }
        }
        // 调整列宽以填充整个表格
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // 调整行高
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
         ui->tableWidget->setRowHeight(i, 50); // 根据需要设置合适的行高
        }
    }
}
// 20240720--在线音乐播放请求
void ListWidget::onlinePlayMusic(const QString &musicName, const QString &artistName, const QString &albumName)
{
    QJsonObject jsonObj;
    jsonObj["request"] = "OnlinePlayMusic";
    jsonObj["MusicName"] = musicName;
    jsonObj["ArtistName"] = artistName;
    jsonObj["AlbumName"] = albumName;

    QByteArray content = QJsonDocument(jsonObj).toJson();
    size_t size = static_cast<size_t>(content.size());
    content.insert(0, reinterpret_cast<const char*>(&size), sizeof(size_t));
    CSocket->sendData(content);
    qDebug() << "发送在线播放请求: " << content;
}
// 20240721--在线音乐海报切换
QString ListWidget::getAlbumPoster(const QString &albumName)
{
    QString posterFileName = albumName + ".png";
    QString posterFilePath = "../Client/Cache/" + posterFileName;
    // 检查本地文件是否存在
    QFileInfo fileInfo(posterFilePath);
    if (fileInfo.exists() && fileInfo.isFile())
    {
        // 如果文件存在，返回路径
        return posterFilePath;
    }
    // 如果本地文件不存在或无法加载，则使用默认海报
    QString defaultPosterFilePath = R"(D:\QT259\Client\image\LRC_background_image.png)"; // 默认海报路径
    QFileInfo defaultFileInfo(defaultPosterFilePath);
    if (defaultFileInfo.exists() && defaultFileInfo.isFile())
    {
        return defaultPosterFilePath;
    }
    else
    {
        qDebug() << "Failed to load default poster from file:" << defaultPosterFilePath;
    }
    // 如果默认海报也不存在，则返回一个空路径
    return QString();
}

// 20240719--处理行双击事件
void ListWidget::onTableCellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);// 忽略列参数
    // 获取双击的歌曲名称
    QString songName = ui->tableWidget->item(row, 0)->text();
    QString singer = ui->tableWidget->item(row, 1)->text();
    QString album = ui->tableWidget->item(row, 2)->text();
    // 更新当前播放音乐的标签
    ui->label_currentPlayMusic->setText(songName);
    // 处理播放逻辑
    qDebug() << "当前点击的歌曲:" << songName << "歌手:" << singer << "专辑:" << album;
    // 在这里实现播放歌曲的逻辑
    onlinePlayMusic(songName, singer, album);



}

// 20240721__加载我喜欢的列表
void ListWidget::loadFavorites()
{
    // 切换界面的显示状态
    if (ui->tableWidget->isVisible())
    {
        ui->tableWidget->hide();
    }
    else
    {
        ui->tableWidget->show();
        // 清空表格
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);

        QString username = getUsername(); // 获取用户名
        // 使用QString的arg函数替换路径中的占位符
        QString path = QString("D:/QT259/build-Client-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/Localfolder/%1/music_resources/likemusic.xml").arg(username);
        // 创建 QFile 对象
        // 打开 XML 文件
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning() << "无法打开 XML 文件";
            return;
        }
        /*读出xml内容*/
        auto Content = file.readAll();
        file.close();
        QString errorMsg;
        int line, column;
        QDomDocument doc;
        if (doc.setContent(Content, &errorMsg, &line, &column) == false)  //doc.setContent()  从文本中读取数据并进行解析
        {
             qDebug()<<"line : "<<line<<" column : "<<column<<" msg : "<<errorMsg<<endl;
             return;
        }
        qDebug()<<"xml解析成功!\n";
        qDebug()<<"当前所属账户： "<< username;
        QDomElement root = doc.documentElement();// 获取xml根元素
        QDomNodeList songNodes = root.elementsByTagName("歌曲");//获取根元素下所有名为 歌曲 的子节点
        // 填充表格
        for (int i = 0; i < songNodes.count(); ++i)
        {
            QDomNode songNode = songNodes.at(i);
            if (songNode.isElement())
            {
                QDomElement songElement = songNode.toElement();
                QString name = songElement.attribute("名称");
                QString singer = songElement.attribute("歌手");
                QString album = songElement.attribute("专辑");
                // 创建只读项
                QTableWidgetItem *nameItem = new QTableWidgetItem(name);
                QTableWidgetItem *singerItem = new QTableWidgetItem(singer);
                QTableWidgetItem *albumItem = new QTableWidgetItem(album);
                // 设置项为只读
                nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
                singerItem->setFlags(singerItem->flags() & ~Qt::ItemIsEditable);
                albumItem->setFlags(albumItem->flags() & ~Qt::ItemIsEditable);
                // 添加一行到表格
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                ui->tableWidget->setItem(row, 0, nameItem);
                ui->tableWidget->setItem(row, 1, singerItem);
                ui->tableWidget->setItem(row, 2, albumItem);
                qDebug() << "名称: " << name << ", 歌手: " << singer << ", 专辑: " << album;
            }
        }
        // 调整列宽以填充整个表格
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // 调整行高
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
         ui->tableWidget->setRowHeight(i, 50); // 根据需要设置合适的行高
        }
    }
}

// 20240722__我喜欢点击事件
void ListWidget::myLikeMusicClicked()
{
    // 获取标签中的当前播放音乐名称
    QString songName = ui->label_currentPlayMusic->text();
    if(songName.isEmpty())
    {
        qDebug()<< "没有当前播放音乐的信息";
        return;
    }
    // 查找表格中对应的音乐信息
    int rowCount = ui->tableWidget->rowCount();
    QString singer;
    QString album;
    bool found = false;
    for(int row = 0; row < rowCount; ++row)
    {
        QString name = ui->tableWidget->item(row, 0)->text();
        if(name == songName)
        {
            singer = ui->tableWidget->item(row, 1)->text();
            album = ui->tableWidget->item(row, 2)->text();
            found = true;
            break;
        }
    }
    if (!found)
    {
        qWarning() << "在表格中未找到音乐信息";
        return;
    }
    // 调用函数添加或删除音乐到/从我喜欢的音乐列表
    addToMyLikeMusicList(songName, singer, album);
    qDebug() << "本地处理成功" << endl;
}
// 20240722__添加到我喜欢的列表
void ListWidget::addToMyLikeMusicList(const QString &songName, const QString &singer, const QString &album)
{
    QString username = getUsername(); // 获取用户名
    QString path = QString("D:/QT259/build-Client-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/Localfolder/%1/music_resources/likemusic.xml").arg(username);
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "无法打开 XML 文件";
        return;
    }
    // 读取现有内容
    QByteArray content = file.readAll();
    file.close();

    QDomDocument doc;
    QString errorMsg;
    int line, column;
    if (!doc.setContent(content, &errorMsg, &line, &column))
    {
        qDebug() << "XML解析错误:" << errorMsg;
        return;
    }
    QDomElement root = doc.documentElement();
    QDomNodeList songNodes = root.elementsByTagName("歌曲");

    bool found = false;
    for (int i = 0; i < songNodes.count(); ++i)
    {
        QDomNode songNode = songNodes.at(i);
        if (songNode.isElement())
        {
            QDomElement songElement = songNode.toElement();
            if (songElement.attribute("名称") == songName &&
                songElement.attribute("歌手") == singer &&
                songElement.attribute("专辑") == album)
            {
                // 如果找到了，则从文档中删除
                root.removeChild(songNode);
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        // 如果没有找到，添加新音乐
        QDomElement songElement = doc.createElement("歌曲");
        songElement.setAttribute("名称", songName);
        songElement.setAttribute("歌手", singer);
        songElement.setAttribute("专辑", album);
        root.appendChild(songElement);
    }
    // 保存 XML 文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "无法打开 XML 文件进行写入";
        return;
    }
    QTextStream stream(&file);
    doc.save(stream, 4); // 保存 XML 文件，缩进为4个空格
    file.close();
    // 发送请求到服务器
    sendFavoriteUpdateRequest(songName, singer, album, !found);
}
// 20240722__发送我喜欢请求
void ListWidget::sendFavoriteUpdateRequest(const QString &songName, const QString &singer, const QString &album, bool add)
{
    QJsonObject jsonObj;
    jsonObj["request"] = "handleAddOrRemoveFavorite";
    jsonObj["status"] = add ? "AddToFavorites" : "RemoveFromFavorites";
    jsonObj["MusicName"] = songName;
    jsonObj["ArtistName"] = singer;
    jsonObj["AlbumName"] = album;

    // 获取当前用户名
    QString username = getUsername();
    jsonObj["username"] = username;

    QByteArray content = QJsonDocument(jsonObj).toJson();
    size_t size = static_cast<size_t>(content.size());
    content.insert(0, reinterpret_cast<const char*>(&size), sizeof(size_t));
    CSocket->sendData(content);
    qDebug() << (add ? "发送添加到收藏请求" : "发送从收藏中删除请求") << ":" << content;
}



