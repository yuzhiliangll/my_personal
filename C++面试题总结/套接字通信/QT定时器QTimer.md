在进行窗口程序的处理过程中, 经常要周期性的执行某些操作, 或者制作一些动画效果，看似比较复杂的问题使用定时器就可以完美的解决这些问题， Qt中提供了两种定时器方式一种是使用Qt中的事件处理函数这个在后续章节会给大家做细致的讲解，本节主要给大家介绍一下Qt中的定时器类 QTimer的使用方法。

要使用它，只需创建一个QTimer类对象，然后调用其 start() 函数开启定时器，此后QTimer对象就会周期性的发出 timeout() 信号。我们先来了解一下这个类的相关API。

1. public/slot function
```C++
// 构造函数
// 如果指定了父对象, 创建的堆内存可以自动析构
QTimer::QTimer(QObject *parent = nullptr);

// 设置定时器时间间隔为 msec 毫秒
// 默认值是0，一旦窗口系统事件队列中的所有事件都已经被处理完，一个时间间隔为0的QTimer就会触发
void QTimer::setInterval(int msec);
// 获取定时器的时间间隔, 返回值单位: 毫秒
int QTimer::interval() const;

// 根据指定的时间间隔启动或者重启定时器, 需要调用 setInterval() 设置时间间隔
[slot] void QTimer::start();
// 启动或重新启动定时器，超时间隔为msec毫秒。
[slot] void QTimer::start(int msec);
// 停止定时器。
[slot] void QTimer::stop();

// 设置定时器精度
/*
参数: 
    - Qt::PreciseTimer -> 精确的精度, 毫秒级
    - Qt::CoarseTimer  -> 粗糙的精度, 和1毫秒的误差在5%的范围内, 默认精度
    - Qt::VeryCoarseTimer -> 非常粗糙的精度, 精度在1秒左右
*/
void QTimer::setTimerType(Qt::TimerType atype);
Qt::TimerType QTimer::timerType() const;	// 获取当前定时器的精度

// 如果定时器正在运行，返回true; 否则返回false。
bool QTimer::isActive() const;

// 判断定时器是否只触发一次
bool QTimer::isSingleShot() const;
// 设置定时器是否只触发一次, 参数为true定时器只触发一次, 为false定时器重复触发, 默认为false
void QTimer::setSingleShot(bool singleShot);
2. signals
这个类的信号只有一个, 当定时器超时时，该信号就会被发射出来。给这个信号通过conect()关联一个槽函数, 就可以在槽函数中处理超时事件了。

C++
1
[signal] void QTimer::timeout();
3. static public function
C++
// 其他同名重载函数可以自己查阅帮助文档
/*
功能: 在msec毫秒后发射一次信号, 并且只发射一次
参数:
	- msec:     在msec毫秒后发射信号
	- receiver: 接收信号的对象地址
	- method:   槽函数地址
*/
[static] void QTimer::singleShot(
        int msec, const QObject *receiver, 
        PointerToMemberFunction method);
4. 定时器使用举例
周期性定时器
C++
// 创建定时器对象
QTimer* timer = new QTimer(this);

// 修改定时器对象的精度
timer->setTimerType(Qt::PreciseTimer);

// 按钮 loopBtn 的点击事件
// 点击按钮启动或者关闭定时器, 定时器启动, 周期性得到当前时间
connect(ui->loopBtn, &QPushButton::clicked, this, [=]()
{
    // 启动定时器
    if(timer->isActive())
    {
        timer->stop();  // 关闭定时器
        ui->loopBtn->setText("开始");
    }
    else
    {
        ui->loopBtn->setText("关闭");
        timer->start(1000); // 1000ms == 1s
    }
});

connect(timer, &QTimer::timeout, this, [=]()
{
    QTime tm = QTime::currentTime();
    // 格式化当前得到的系统时间
    QString tmstr = tm.toString("hh:mm:ss.zzz");
    // 设置要显示的时间
    ui->curTime->setText(tmstr);
});

一次性定时器
C++
// 点击按钮 onceBtn 只发射一次信号
// 点击按钮一次, 发射一个信号, 得到某一个时间点的时间
connect(ui->onceBtn, &QPushButton::clicked, this, [=]()
{
     // 获取2s以后的系统时间, 不创建定时器对象, 直接使用类的静态方法
    QTimer::singleShot(2000, this, [=](){
        QTime tm = QTime::currentTime();
        // 格式化当前得到的系统时间
        QString tmstr = tm.toString("hh:mm:ss.zzz");
        // 设置要显示的时间
        ui->onceTime->setText(tmstr);
    });
});
```
=====================================================================================

很多人不了解Qt Quick和Qml，还有很多人对其存在偏见。这篇文章就是来向这些有困惑的人介绍一下其是什么，有什么特点。

首先，这两个是一个东西吗？
答案：是的。但是，具体来说，Qt Quick是框架，qml是语言。Qt Quick是用C++搭建起来的一套DirectUI/Immediate UI框架，在这个框架上可以用和js语法一样的qml语言开发界面。

和原来的QWidgets框架有什么关系吗？
答案是没有。这个估计让很多人失望，我一开始也是以为Qt Quick就是QWidgets的演进版，只不过用js替代了原有的ui.xml文件。实际上，Qt Quick是一个新框架，它仅仅继承了QT原有的元对象系统，也就带信号槽的对象系统，其他的理念都是新的。了解DirectUI的同学肯定知道DirectUI和经典的GUI库，如MFC、WTL的区别。DirectUI把所有控件都在一个主窗口的绘制事件里绘制，从硬件原理上说就是界面是统一刷新的，而不是根据事件选择部分区域刷新。这样的好处是这些控件容易协作变化，特别适合制作动态界面，例如控件拖拽、变形、变色、皮肤、透明、3D等等。

为什么要引入qml或者说javascript？
答案是提高开发效率。

传统上native的UI开发普遍使用C++，C#，java或者Objective-C，基本上是一类语言，就是静态语言。但是近年来本地应用也有使用HTML5+js的趋势。这个趋势一是因为web技术让js的解析速度更快了，另一方面是硬件资源越来越丰富了。当然最关键的是google开源了其牛逼的js引擎。Node.js加上一个前端框架也可以开发本地应用了。
QT Quick的目的就是提供一套类似的但是集成程度更高的解决方案，Qt Quick内部集成了google V8引擎作为qml的解释器，摒弃了html，起而代之的是直接使用js作为UI的设计语言，qml的意思是Qt Markable Language。
和Node.js类似，Qt Quick也提供了一系列js和C++交互的接口，便于js和C++通信。复杂逻辑、文件系统、网络通信、传感器（像摄像头）的操作都可以在C++侧完成。而界面设计和一些简单逻辑（例如按钮变色、换肤、变形等）都可以在js侧完成。这样避免了传统上本地应用开发前端设计和后台逻辑混合的情况，让界面设计者专心设计界面成为了可能。由于C++提供了内存的快速操作方法（也可以使用js的Typed Array），这种方案的开发效率更高、运行速度还不慢。
只有移动端适合用Qt Quick吗?
答案是否定的。我自己就是使用Qt Quick开发桌面应用的，而且很重型，还是实时的。Qt Quick适合桌面的开发，不仅仅是因为Qt Quick提供了js和C++的交互接口，而且是因为越来越多的桌面应用需要动态界面，有的还是3D界面。

如前文所说，Qt Quick的优点就在于它是DirectUI，其构造界面的机制充分考虑了控件实时动态变化的情形，所以只要是应用是动态界面，那么Qt Quick就是适合的，例如仿真系统、监控系统、游戏等等。
有什么应用是不适合的吗，当然，如果界面中有大量静态控件，例如邮箱，表格或者像Ps这样按钮特别多的复杂界面就是静态界面，界面中有大片的区域不需要刷新，那么就不适合用Qt Quick，因为全局刷新会消耗更多CPU和内存资源。


