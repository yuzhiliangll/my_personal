#include "musicplayer.h"
#include "ui_musicplayer.h"
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


MusicPlayer::MusicPlayer(QWidget *parent, MyClientSocket *socket) :
    QWidget(parent),
    ui(new Ui::MusicPlayer),
    currentPlayMode(ListLoop), // 初始化播放模式
    CSocket(socket)// 初始化套接字指针
{
    ui->setupUi(this);// 如果你使用了 Qt Designer 来设计 UI，需要调用这个函数
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
    ml = new LocalMusicList();// 文件列表--用的是多态

    // 20240704--海报旋转已经写死--待实现对应海报的切换
    // 设置旋转小部件
    //ui->listWidget_musicposter->setFixedSize(200, 180);  // 设置合适的固定尺寸
    // 手动布局
    this->rw = new RotateWidget;
    rw->SetPixMap(QPixmap(R"(D:\QT259\Client\image\LRC_background_image.png)"));
    QHBoxLayout * layout = new  QHBoxLayout;
    layout->addWidget(rw);// 塞进去
    ui->listWidget_musicposter->setLayout(layout);

    //获取音乐列表和初始化
    InitMusicList();// 初始化调用

    // 设置界面标题
    this->setWindowTitle("Music player");
    // 设置窗口图标
    this->setWindowIcon(QIcon(":/image/logo.png"));
    // 设置窗口透明度
    this->setWindowOpacity(0.92); // 透明度值范围为 0.0 (完全透明) 到 1.0 (不透明)

    // 创建QMovie对象并设置GIF动画
    QMovie *movie = new QMovie(":/image/gif_one.gif");
    // 设置QMovie到QLabel中显示动画
    ui->label_gif_one->setMovie(movie);
    // 开始播放动画
    movie->start();
    // 设置QLabel适应内容大小
    ui->label_gif_one->setScaledContents(true);


    ui->Play->setIcon(QIcon(":/image/Play.png"));
    ui->Prev->setIcon(QIcon(":/image/Prev.png"));
    ui->Next->setIcon(QIcon(":/image/Next.png"));
    ui->pushButton_volume->setIcon(QIcon(":/image/volume.png"));// 音量

    // 设置百度超链接文本和样式
    ui->label_baidu->setText("<a href=\"https://www.baidu.com\" style=\"font-family: 'Bauhaus 93'; font-size: 14px;\">百度</a>");
    ui->label_baidu->setOpenExternalLinks(true);


    // 更新播放 默认是列表模式之后的随机播放模式
    updatePlayModeIcon();

    // 信号 和 槽 机制 ： 其底层原理就是回调机制
    // connect(信号的发出者  , 信号(函数)  ,  信号的接收者 , 槽函数(做出响应的函数));
    connect(ui->Play, &QPushButton::clicked, this, &MusicPlayer::playStateChanged);
    connect(ui->pushButton_volume, &QPushButton::clicked, this, &MusicPlayer::VolumeWidgetChanged);
    // 上一首歌
    connect(ui->Prev, &QPushButton::clicked, this, &MusicPlayer::PlayPrev);
    // 下一首歌
    connect(ui->Next, &QPushButton::clicked, this, &MusicPlayer::PlayNext);

    // 播放
    connect(player, &QMediaPlayer::durationChanged, this, &MusicPlayer::DurationChanged);
    // 当前播放的进度
    connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::PositionChanged);
    // 在构造函数中连接播放结束信号
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MusicPlayer::mediaStatusChanged);

    // 滑轨拖动，让音乐播放的进度改变
    connect(ui->horizontalSlider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(ui->verticalSlider, &QSlider::sliderMoved, this, &MusicPlayer::VolumeChanged);// 音量修改
    connect(ui->verticalSlider, &QSlider::valueChanged, this, &MusicPlayer::VolumeChanged);
    // 连接滑块数值变化信号
    connect(ui->verticalSlider, &QSlider::valueChanged, this, &MusicPlayer::updateVolumeLabel);
    ui->verticalSlider->setRange(0, 100);
    // 初始值设置
    ui->verticalSlider->setValue(100);
    // 音量按之前 隐藏
    ui->verticalSlider->hide();
    // 设置音量更新标签的初始值
    ui->label_updateVolume->setText(QString::number(ui->verticalSlider->value()));


    // 定时器设置
    timer.setInterval(500);// // 设置一个较短的定时器间隔---检查一次
    // 歌词显示(timer 是一个指针)
    connect(&timer, &QTimer::timeout, this, &MusicPlayer::ChangedLRC);
    connect(ui->LRCShow, &QPushButton::clicked, this, &MusicPlayer::LRCIsShow);// 20240718--是否显示
    // 双击音乐列表
    connect(ui->listWidget, &QListWidget::doubleClicked, this, &MusicPlayer::PlayMusic);
    ui->listWidget->hide();// 默认隐藏
    // 是否显示已下载的播放歌单
    connect(ui->showDownloadListPlayButton, &QPushButton::clicked, this, &MusicPlayer::downloadMusicListIsHidden);
    // 切换--播放模式
    connect(ui->pushButton_playmode, &QPushButton::clicked, this, &MusicPlayer::ChangePlayMode);

    // 音乐下载_请求---带迁移到音乐播放器模块--待完成
    connect(ui->pushButton_downloadmusic, &QPushButton::clicked, this, &MusicPlayer::promptForMusicName); // 连接信号到槽
    // 接收数据时处理
    connect(CSocket, &MyClientSocket::DataRecv, this, &MusicPlayer::handleMusicDataRecv); // 连接信号到槽

    // 20240717--设置下载列表信息界面
    setupDownloadUI();

    // 20240723--在构造函数中初始化线程池
    threadPool = new QThreadPool(this);// 创建一个新的"QThreadPool"实例
    threadPool->setMaxThreadCount(5);
    connect(ui->pushButton_BatchDownload, &QPushButton::clicked, this, &MusicPlayer::onBatchDownloadButtonClicked);


}

MusicPlayer::~MusicPlayer()
{
    delete player;// 记得析构
    delete ui;
    delete threadPool;
}

void MusicPlayer::InitMusicList()
{
    // 清空列表项
    ui->listWidget->clear();
    // 获取音乐列表信息
    MusicListInfo = ml->GetMusicList();
    for(auto ite = MusicListInfo.begin(); ite != MusicListInfo.end(); ite++)
    {
        ui->listWidget->addItem(ite->first);
    }
}

long GetMusicTime(QString& str)
{
    str.remove(0, 1);// 删除开头的 '['

    auto minute = str.split(":")[0].toInt();
    auto msecond = str.split(".")[1].toInt();
    auto second = str.split(":")[1].split(".")[0].toInt();

    return minute * 60 * 1000 + second * 1000 + msecond;
}

// 歌词解析
void MusicPlayer::AnalysisLRC(const QStringList &LRCList)
{
    LRCMap.clear();// 清空
    for(auto ite = LRCList.begin(); ite != LRCList.end(); ite++)
    {
        auto InfoList = ite->split("]");
        if(InfoList.size() != 2)
        {
            continue;// 过滤
        }
        LRCMap.insert({GetMusicTime(InfoList[0]), InfoList[1]});
    }
}

// 播放状态
void MusicPlayer::playStateChanged()
{
    // 判断是否正在播放
    if(player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();// 暂停
        rw->Stop();
        ui->Play->setIcon(QIcon(":/image/Play.png"));
        timer.stop();

    }
    else
    {
        player->play();// 播放
        rw->Start();
        ui->Play->setIcon(QIcon(":/image/Pause.png"));
        timer.start();// 启动定时器
    }
}

// 更新总时长
void MusicPlayer::DurationChanged()
{
    qint64 duration = player->duration();// 使用 qint64 类型来存储持续时间，确保足够大的范围
    // 将这个数值转换为QString类型
    QString timeStr = QString::number(duration / 1000 / 60)// 计算分钟
            + ":"
            + QString::number(duration / 1000 % 60);       // 计算秒钟
    ui->label_TotalTime->setText(timeStr);


    // 总长度 给到滑轨
    ui->horizontalSlider->setRange(0, static_cast<int>(duration));// 将 qint64 类型转换为 int 类型
}

// 更新当前播放位置
void MusicPlayer::PositionChanged()
{
    qint64 pos = player->position();// 使用 qint64 类型来存储当前播放位置
    QString timeStr = QString::number(pos / 1000 / 60)
                        + ":"
                        + QString::number(pos / 1000 % 60);
    ui->label_CurrentTime->setText(timeStr);
    // 滑轨定位
    ui->horizontalSlider->setValue(static_cast<int>(pos));
}

void MusicPlayer::VolumeWidgetChanged()
{
    // 按之前隐藏
    if (ui->verticalSlider->isHidden())
    {
        // 按一下显示
        ui->verticalSlider->show();
    }
    else
    {
        ui->verticalSlider->hide();
    }
}


// 音量修改 + 对应图标显示
void MusicPlayer::VolumeChanged()
{
    int volume = ui->verticalSlider->value();
    player->setVolume(volume);

    // 如果滑块的值为0，表示音量被调整到最低
    if (volume == 0)
    {
        // 可以在这里添加额外的操作，比如静音图标等
        ui->pushButton_volume->setIcon(QIcon(":/image/Muted.png"));// 静音
    }
    else if (volume <= 60)
    {
        ui->pushButton_volume->setIcon(QIcon(":/image/VolumeLow.png")); // 低音量图标
    }
    else
    {
        ui->pushButton_volume->setIcon(QIcon(":/image/VolumeHigh.png")); // 高音量图标
    }

}

// 更新音量数值显示
void MusicPlayer::updateVolumeLabel(int value)
{
    ui->label_updateVolume->setText(QString::number(value));
}

// 对应的播放时间->显示歌词
void MusicPlayer::ChangedLRC()
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
    QLabel* labels[] = {ui->label_LRC, ui->label_LRC_1, ui->label_LRC_2, ui->label_LRC_3, ui->label_LRC_4, ui->label_LRC_5, ui->label_LRC_6};

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
// 20240718歌词控件是否隐藏
void MusicPlayer::LRCIsShow()
{
    if (ui->widget->isVisible())
    {
        ui->widget->hide();
    }
    else
    {
        ui->widget->show();
    }
}
// 重置所有歌词标签的样式
void MusicPlayer::resetLRCLabels()
{
    QLabel* labels[] = {ui->label_LRC, ui->label_LRC_1, ui->label_LRC_2, ui->label_LRC_3, ui->label_LRC_4, ui->label_LRC_5, ui->label_LRC_6};
    for (int i = 0; i < 7; ++i)
    {
        labels[i]->setText("");
        labels[i]->setStyleSheet("");
    }
}


// 20240717--通过歌曲名使用递归来设置海报
void MusicPlayer::switchPoster(const QString& musicName)
{
    // 构造根目录路径
    QString rootPath = "D:/QT259/Client/DownloadMusic/";
    // 构造歌曲文件名（假设音乐文件后缀为 .mp3）
    QString musicFileName = musicName + ".mp3";
    // 调用递归函数查找海报路径
    QString posterPath = findPoster(rootPath, musicFileName);
    // 设置旋转小部件的海报图片
    if(!posterPath.isEmpty() && QFile::exists(posterPath))
    {
        qDebug() << "设置海报: " << posterPath;
        rw->SetPixMap(QPixmap(posterPath)); // 使用找到的海报路径创建 QPixmap 对象，并设置给旋转小部件 rw
    }
    else
    {
        qDebug() << "未找到海报，使用默认背景图片";
        rw->SetPixMap(QPixmap(R"(D:\QT259\Client\image\LRC_background_image.png)")); // 如果未找到海报，则使用默认背景图片
    }
}
QString MusicPlayer::findPoster(const QString& currentPath, const QString& musicFileName)
{
    QDir rootDir(currentPath); // 创建 QDir 对象，表示当前目录路径

    // 获取当前目录中的所有文件和子目录信息列表
    QFileInfoList entryList = rootDir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);// 排除 "." 和 ".." 目录
    // 遍历文件和子目录信息列表
    foreach (QFileInfo entryInfo, entryList)
    {
        if (entryInfo.isDir()) // 如果是目录
        {
            // 递归查找子目录中的海报
            QString posterPath = findPoster(entryInfo.absoluteFilePath(), musicFileName);
            if (!posterPath.isEmpty())
            {
                return posterPath;// 返回找到的海报路径
            }
        }
        else if (entryInfo.fileName() == musicFileName) // 如果是音乐文件
        {
            QString musicDirPath = entryInfo.absolutePath(); // 获取音乐文件的目录路径
            QDir musicDir(musicDirPath);
            QFileInfoList pngFiles = musicDir.entryInfoList(QStringList("*.png"), QDir::Files | QDir::NoSymLinks); // 查找该目录中的 .png 文件

            if (pngFiles.size() == 1) // 如果找到唯一的 .png 文件
            {
                QString posterPath = pngFiles.at(0).absoluteFilePath();
                qDebug() << "找到海报: " << posterPath;
                return posterPath;
            }
        }
    }

    // 如果当前路径及其子路径中都没有找到符合条件的 .png 文件，返回空字符串
    return "";
}

void MusicPlayer::PlayMusic()
{
    // 被点击的当前节点
    auto ite = MusicListInfo.find(ui->listWidget->currentItem()->text());
    if (ite == MusicListInfo.end())
    {
        qDebug()<< "未找到该音乐文件"<<endl;
        return;
    }
    // 设置当前播放的歌曲信息
    AnalysisLRC(ml->GetLRC(ui->listWidget->currentItem()->text()));
    player->setMedia(ite->second);
    playStateChanged();
    // 更换显示当前歌曲名称
    ui->label_currentPlayMusicName->setText(ui->listWidget->currentItem()->text());
    // 设置字体和颜色
    ui->label_currentPlayMusicName->setStyleSheet("font: 9pt 'Bauhaus 93'; color: white;");
    // 切换专辑海报
    switchPoster(ui->listWidget->currentItem()->text());
    // 播放结束自动播放下一首歌曲的处理已经在 mediaStatusChanged 槽函数中实现了，无需重复处理

}

// 播放结束信号处理槽函数
// 信号且状态为 QMediaPlayer::EndOfMedia 时，自动切换到下一首歌曲
void MusicPlayer::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        PlayNext();
    }
}

void MusicPlayer::PlayPrev()
{
    // 增加模式选择后进行修改
    // 列表中获取当前选中的位置
    int currentIndex = ui->listWidget->currentRow();

    switch (currentPlayMode)
    {
    case ListLoop:
    case Sequential:// 计算上一首歌的索引
        currentIndex = (currentIndex - 1 + ui->listWidget->count()) % ui->listWidget->count();// 使用模运算确保索引在范围内，即如果索引为负数，会循环到列表的末尾
        break;
    case Random:
        currentIndex = qrand() % ui->listWidget->count();// 随机选择列表中的一首歌
        break;
    case SingleLoop:
        // 单曲循环不改变 currentIndex
        break;
    }

    ui->listWidget->setCurrentRow(currentIndex);// 设置当前选中行的索引
    PlayMusic();
    // 重置所有歌词标签的样式
    resetLRCLabels();
}

void MusicPlayer::PlayNext()
{
    // 列表中获取当前选中的位置
    int currentIndex = ui->listWidget->currentRow();

    switch (currentPlayMode)
    {
    case ListLoop:// 计算下一首歌的索引
        currentIndex = (currentIndex + 1) % ui->listWidget->count();// 模运算确保索引在范围内
        break;
    case Sequential:
        currentIndex = (currentIndex + 1);
        if (currentIndex >= ui->listWidget->count())
        {
            currentIndex = 0;// 到达列表末尾，则循环到列表的开头
        }
        break;
    case Random:
        currentIndex = qrand() % ui->listWidget->count();
        break;
    case SingleLoop:
        // 单曲循环不改变 currentIndex
        break;
    }

    ui->listWidget->setCurrentRow(currentIndex);
    PlayMusic();
    // 重置所有歌词标签的样式
    resetLRCLabels();
}

// 切换播放模式
void MusicPlayer::ChangePlayMode()
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
    updatePlayModeIcon();
}

// 更新播放模式图标
void MusicPlayer::updatePlayModeIcon()
{
    switch (currentPlayMode)
    {
    case Sequential:
        ui->pushButton_playmode->setIcon(QIcon(":/image/Sequentialplay.png"));
        break;
    case ListLoop:
        ui->pushButton_playmode->setIcon(QIcon(":/image/ListMode.png"));
        break;
    case SingleLoop:
        ui->pushButton_playmode->setIcon(QIcon(":/image/Singlecycle.png"));
        break;
    case Random:
        ui->pushButton_playmode->setIcon(QIcon(":/image/Shuffleplay.png"));
        break;
    }
}

void MusicPlayer::handleMusicDataRecv(QByteArray array)// -----
{
    // -------处理接受的数据
    // 音乐文件下载或者 20240720--在线播放数据
    auto rootObj = QJsonDocument::fromJson(array).object();// 将接收到的字节数组转换为 QJsonDocument 对象
    QString status = rootObj["status"].toString();
    QString fileName = rootObj["FileName"].toString();// 获取文件名
    QString artistName = rootObj["ArtistName"].toString(); // 获取歌手名
    QString albumName = rootObj["AlbumName"].toString(); // 获取专辑名
    QString response = rootObj["response"].toString();// 20240723--

    static QString currentDownloadFile = ""; // 20240722用于记录当前下载的文件名

    static QString currentDownloadType = ""; // 20240723--用于批量下载当前下载类型（音乐、歌词、海报）


    if (status == "Download")
    {
        QString basePath = "../Client/DownloadMusic/";
        QString fullPath = basePath + artistName + "/" + albumName + "/";

        QDir dir;
        if (!dir.exists(fullPath))
        {
            dir.mkpath(fullPath); // 创建歌手和专辑文件夹
        }

        QString filePath = fullPath + fileName;
        QFile file(filePath);
        qDebug() << "fileName: " << file.fileName() << endl;

        if (rootObj["request"].toString() == "DownLoadMusic")
        {
            // 判断是否为新的下载请求
            // QIODevice::WriteOnly 模式打开文件，而不是 QIODevice::Append。 QIODevice::WriteOnly 模式会清空文件内容并从头开始写入数据。
            // 可以在处理数据时，判断是否是新的下载请求，如果是新的下载请求则使用 QIODevice::WriteOnly 打开文件，如果是继续下载则使用 QIODevice::Append 模式。
            if (currentDownloadFile != filePath)
            {
                currentDownloadFile = filePath;
                file.open(QIODevice::WriteOnly); // 使用WriteOnly模式打开文件
            }
            else
            {
                file.open(QIODevice::Append); // 继续追加数据
            }
            // file.open(QIODevice::Append);// 直接这样写这一行重复下载会叠加到后面
            file.write(QByteArray::fromHex(rootObj["data"].toString().toUtf8()));//  写入的文件转utf8编码
            qDebug()<<rootObj["ReadSize"]<< endl;
            file.close();

            // 如果下载完成
            if (rootObj.contains("response") && rootObj["response"].toString() == "Download complete")
            {
                QMessageBox::information(this, tr("下载完成"), tr("歌曲下载完成"));
                // 20240717--读取下载到本地文件的信息进行显示
            }

        }
        if (rootObj.contains("response") && rootObj["response"].toString() == "Music not exist")
        {
            qDebug()<< "Music not exist";
            QMessageBox::warning(this, tr("失败"), tr("文件不存在"));
        }
    }
    else if(status == "BatchDownload")// 客户端需要能够接收并正确处理多种类型的文件数据（音乐文件、歌词文件和海报文件）
    {
        QString basePath = "../Client/DownloadMusic/";
        QString fullPath = basePath + artistName + "/" + albumName + "/";

        QDir dir;//设置文件保存路径，并检查是否需要创建目录
        if (!dir.exists(fullPath))
        {
           dir.mkpath(fullPath); // 创建文件夹
        }

        QString filePath = fullPath + fileName;
        QFile file(filePath);

        // 确定下载类型并处理文件
        if (rootObj.contains("FileName"))
        {
            //确定文件类型并打开文件（写入或追加数据）
           QString type = rootObj["FileName"].toString().split('.').last().toLower(); // 文件扩展名

           if (currentDownloadType != type || currentDownloadFile != filePath)
           {
               currentDownloadType = type;
               currentDownloadFile = filePath;
               file.open(QIODevice::WriteOnly); // 重新打开文件进行写入
           }
           else
           {
               file.open(QIODevice::Append); // 追加数据
           }

           file.write(QByteArray::fromHex(rootObj["data"].toString().toUtf8())); // 将接收到的二进制数据写入文件，并关闭文件
           file.close();

           // 检查下载是否完成
           if (response == "BatchDownload completed")
           {
               QMessageBox::information(this, tr("下载完成"), tr("批量下载完成"));
               // 可以在这里处理后续操作
           }
        }
        else if (response == "Music not exist" || response == "Lyric file open error" || response == "Poster file open error")
        {
           qDebug() << response;
           QMessageBox::warning(this, tr("下载失败"), response);
        }
    }
}
// 发送音乐下载请求
void MusicPlayer::DownLoadMusic(const QString& musicName,const QString& artistName, const QString& albumName)
{
    // 构建下载请求的 JSON 数据
    QJsonObject jsonObj;
    jsonObj["request"] = "DownLoadMusic";
    jsonObj["MusicName"] = musicName;// 确定要下载的音乐文件名称
    // 20240714--
    jsonObj["ArtistName"] = artistName; // 确定艺术家名称
    jsonObj["AlbumName"] = albumName; // 确定专辑名称

    // 将 JSON 对象转换为 QByteArray
    QByteArray content = QJsonDocument(jsonObj).toJson();
    size_t size = static_cast<size_t>(content.size());
    content.insert(0, reinterpret_cast<const char*>(&size), sizeof(size_t));
    // -----使用 MyClientSocket 发送登录请求
    CSocket->sendData(content); // 这里假设 MyClientSocket 中有一个 sendData 方法用于发送数据
    qDebug()<< content << endl;
}
// 用于显示输入对话框并获取音乐文件名称
void MusicPlayer::promptForMusicName()
{
    bool ok;// 布尔变量 ok，用于接收 QInputDialog::getText 的状态，判断用户是否点击了“OK”按钮并输入了有效内容
    QString musicName = QInputDialog::getText(this, tr("下载音乐"),
                                         tr("请输入音乐文件名称:"), QLineEdit::Normal,
                                         "", &ok);//输入框为普通的单行编辑框（QLineEdit::Normal），初始值为空字符串。ok 将接收用户的操作结果
    // 20240714__修改
    if (ok && !musicName.isEmpty())
    {
        QString artistName = QInputDialog::getText(this, tr("下载音乐"),
                                                   tr("请输入艺术家名称:"), QLineEdit::Normal,
                                                   "", &ok);
        if (ok && !artistName.isEmpty())
        {
            QString albumName = QInputDialog::getText(this, tr("下载音乐"),
                                                      tr("请输入专辑名称:"), QLineEdit::Normal,
                                                      "", &ok);
            if (ok && !albumName.isEmpty())
            {
                DownLoadMusic(musicName, artistName, albumName);
            }
        }
    }
}
// 设置下载列表信息界面
void MusicPlayer::setupDownloadUI()
{
    // 创建下载列表部件
    downloadListWidget = new QWidget(this);// 创建一个新的 QWidget 对象，作为下载列表的容器部件
    downloadTable = new QTableWidget(this);// 创建一个 QTableWidget 对象，用于显示下载列表的表格

    // 设置下载列表表格的列数和标题
    downloadTable->setColumnCount(3);// 设置表格的列数为 3
    QStringList headers;
    headers << "歌曲名称" << "歌手" << "专辑";
    downloadTable->setHorizontalHeaderLabels(headers);// 设置表头标题
    downloadTable->horizontalHeader()->setStretchLastSection(true);// 自动调整最后一列的宽度以填充剩余空间
    // 使用 QVBoxLayout 布局
    QVBoxLayout *downloadLayout = new QVBoxLayout();//用于下载列表部件的布局
    downloadLayout->addWidget(downloadTable); // 将 downloadTable 添加到布局中
    downloadListWidget->setLayout(downloadLayout);
    // 暂时不用--添加到主布局
//    mainLayout = new QVBoxLayout();
//    mainLayout->addWidget(downloadListWidget);// 将 downloadListWidget 添加到 mainLayout 中
    // 20240718设置 downloadListWidget 的初始位置和大小
    downloadListWidget->setGeometry(130, 100, 300, 230); // 设置初始位置和大小

    // 默认隐藏下载列表控件
    downloadListWidget->hide();
    connect(ui->showDownloadListButton, &QPushButton::clicked, this, &MusicPlayer::showDownloadList);
}
void MusicPlayer::setupDownloadList()
{
    // 清空现有的下载列表
    downloadTable->setRowCount(0);
    // 获取下载音乐的基路径
    QString basePath = "../Client/DownloadMusic/";//指向一个相对路径，即存储下载音乐的基本目录
    QDir baseDir(basePath);//QDir 对象 baseDir，用于表示 basePath 指向的目录
    if (!baseDir.exists())
    {
        qWarning() << "Download base directory does not exist!";
        return;
    }
    // 遍历基路径下的所有艺术家目录,将它们存储在 artistDirs 字符串列表中
    QStringList artistDirs = baseDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);// QDir::Dirs表示只列出目录,第二个参数是忽略. ..目录
    foreach (const QString &artistName, artistDirs)
    {
        QString artistPath = basePath + artistName + "/";// 对于每个艺术家目录，构造完整路径
        QDir artistDir(artistPath);

        // 遍历艺术家目录下的所有专辑目录
        QStringList albumDirs = artistDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        foreach (const QString &albumName, albumDirs)// 循环遍历每个专辑目录将值赋值给 albumName
        {
            QString albumPath = artistPath + albumName + "/";
            QDir albumDir(albumPath);

            // 遍历专辑目录下的所有 .mp3 文件(过滤其他文件)
            QStringList musicFiles = albumDir.entryList(QStringList() << "*.mp3", QDir::Files);
            foreach (const QString &musicName, musicFiles)
            {
                int row = downloadTable->rowCount();// 先获取当前行数
                downloadTable->insertRow(row);// 插入一行
                downloadTable->setItem(row, 0, new QTableWidgetItem(musicName));// 并依次设置三列的内容
                downloadTable->setItem(row, 1, new QTableWidgetItem(artistName));
                downloadTable->setItem(row, 2, new QTableWidgetItem(albumName));
            }
        }
    }
}
void MusicPlayer::showDownloadList()//显示下载列表
{
    if (downloadListWidget->isHidden())
    {
        downloadListWidget->show();
        setupDownloadList(); // 在显示之前更新下载列表
    }
    else
    {
        downloadListWidget->hide();
    }
}

// 20240723--输入批量下载列表
void MusicPlayer::promptForBatchDownload()
{
    bool ok;//ok，用于检查用户是否点击了对话框的“确定”按钮
    // 弹出一个多行文本输入对话框，让用户输入音乐列表。返回的字符串是用户输入的内容
    QString musicListStr = QInputDialog::getMultiLineText(this, tr("批量下载音乐"),
                                                         tr("请输入音乐文件列表，每行一个，格式: 歌曲名称,艺术家名称,专辑名称"),
                                                         "", &ok);

    if (ok && !musicListStr.isEmpty())// 检查用户是否点击了“确定”并且输入框不为空
    {
        QStringList musicList = musicListStr.split("\n");// 将输入的字符串按行分割成一个字符串列表，每行代表一个音乐条目
        QList<QPair<QString, QPair<QString, QString>>> musicDataList;//每个音乐条目用一个 QPair 来表示，QPair 的第一个元素是歌曲名称，第二个元素是一个 QPair，包含艺术家名称和专辑名称

        for (const QString &line : musicList)
        {
            QStringList parts = line.split(",");//将每行按逗号分割成一个字符串列表
            if (parts.size() == 3)
            {
                QString musicName = parts[0].trimmed();//获取每个部分的内容，并去除前后空白。
                QString artistName = parts[1].trimmed();
                QString albumName = parts[2].trimmed();
                musicDataList.append(qMakePair(musicName, qMakePair(artistName, albumName)));
            }
        }

        if (musicDataList.size() >= 3 && musicDataList.size() <= 5)
        {
            sendBatchDownloadRequest(musicDataList);//发送下载请求
        }
        else
        {
            QMessageBox::warning(this, tr("无效的输入"), tr("请输入3到5个有效的音乐文件信息"));
        }
    }
}
/*******************************************************************************************************************/
// 20240723--待实现:发送批量下载请求
// 包含所有音乐条目的信息，并将其传递给 DownloadTask 类的实例
void MusicPlayer::sendBatchDownloadRequest(const QList<QPair<QString, QPair<QString, QString>>>& musicDataList)
{
    QJsonArray musicArray;//用于存储音乐条目的 JSON 对象
    for (const auto &musicData : musicDataList)//遍历 musicDataList
    {
        QJsonObject musicObj;//为每个音乐条目创建 QJsonObject
        musicObj["MusicName"] = musicData.first;
        musicObj["ArtistName"] = musicData.second.first;
        musicObj["AlbumName"] = musicData.second.second;
        musicArray.append(musicObj);
    }

    DownloadTask *task = new DownloadTask(musicArray, CSocket);//创建一个新的下载任务，将 JSON 数组和 CSocket 传递给它
    connect(task, &DownloadTask::downloadCompleted, this, &MusicPlayer::handleBatchDownload);
    threadPool->start(task);//将任务添加到线程池中执行
}

void MusicPlayer::handleBatchDownload(const QByteArray &content)
{
    CSocket->sendData(content);
    qDebug() << "Sent batch download request";
    qDebug() << " content =  " << content ;
}

void MusicPlayer::onBatchDownloadButtonClicked()
{
    promptForBatchDownload();
}

// 下载的歌单显示
void MusicPlayer::downloadMusicListIsHidden()
{
    if (ui->listWidget->isHidden())
    {
        ui->listWidget->show();
    }
    else
    {
        ui->listWidget->hide();
    }
}


