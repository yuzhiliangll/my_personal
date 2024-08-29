C++11之前，C++语言没有对并发编程提供语言级别的支持，这使得我们在编写可移植的并发程序时，存在诸多的不便。现在C++11中增加了线程以及线程相关的类，很方便地支持了并发编程，使得编写的多线程程序的可移植性得到了很大的提高。

C++11中提供的线程类叫做std::thread，基于这个类创建一个新的线程非常的简单，只需要提供线程函数或者函数对象即可，并且可以同时指定线程函数的参数。我们首先来了解一下这个类提供的一些常用API：

1. 构造函数
```C++

// ①
thread() noexcept;
// ②
thread( thread&& other ) noexcept;
// ③
template< class Function, class... Args >
explicit thread( Function&& f, Args&&... args );
// ④
thread( const thread& ) = delete;
构造函数①：默认构造函，构造一个线程对象，在这个线程中不执行任何处理动作

构造函数②：移动构造函数，将 other 的线程所有权转移给新的thread 对象。之后 other 不再表示执行线程。

构造函数③：创建线程对象，并在该线程中执行函数f中的业务逻辑，args是要传递给函数f的参数

任务函数f的可选类型有很多，具体如下：

普通函数，类成员函数，匿名函数，仿函数（这些都是可调用对象类型）
可以是可调用对象包装器类型，也可以是使用绑定器绑定之后得到的类型（仿函数）
构造函数④：使用=delete显示删除拷贝构造, 不允许线程对象之间的拷贝

2. 公共成员函数
2.1 get_id()
应用程序启动之后默认只有一个线程，这个线程一般称之为主线程或父线程，通过线程类创建出的线程一般称之为子线程，每个被创建出的线程实例都对应一个线程ID，这个ID是唯一的，可以通过这个ID来区分和识别各个已经存在的线程实例，这个获取线程ID的函数叫做get_id()，函数原型如下：

C++
1
std::thread::id get_id() const noexcept;
示例程序如下：

C++
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void func(int num, string str)
{
    for (int i = 0; i < 10; ++i)
    {
        cout << "子线程: i = " << i << "num: " 
             << num << ", str: " << str << endl;
    }
}

void func1()
{
    for (int i = 0; i < 10; ++i)
    {
        cout << "子线程: i = " << i << endl;
    }
}

int main()
{
    cout << "主线程的线程ID: " << this_thread::get_id() << endl;
    thread t(func, 520, "i love you");
    thread t1(func1);
    cout << "线程t 的线程ID: " << t.get_id() << endl;
    cout << "线程t1的线程ID: " << t1.get_id() << endl;
}
thread t(func, 520, "i love you");：创建了子线程对象t，func()函数会在这个子线程中运行
func()是一个回调函数，线程启动之后就会执行这个任务函数，程序猿只需要实现即可
func()的参数是通过thread的参数进行传递的，520,i love you都是调用func()需要的实参
线程类的构造函数③是一个变参函数，因此无需担心线程任务函数的参数个数问题
任务函数func()一般返回值指定为void，因为子线程在调用这个函数的时候不会处理其返回值
thread t1(func1);：子线程对象t1中的任务函数func1()，没有参数，因此在线程构造函数中就无需指定了
通过线程对象调用get_id()就可以知道这个子线程的线程ID了，t.get_id()，t1.get_id()。
```
=========================================================================

基于命名空间 this_thread 得到当前线程的线程ID
在C++11中不仅添加了线程类，还添加了一个关于线程的命名空间std::this_thread，在这个命名空间中提供了四个公共的成员函数，通过这些成员函数就可以对当前线程进行相关的操作了。

1. get_id()
调用命名空间std::this_thread中的get_id()方法可以得到当前线程的线程ID，函数原型如下：

```C++
1
thread::id get_id() noexcept;
关于函数使用对应的示例代码如下：

C++
#include <iostream>
#include <thread>
using namespace std;

void func()
{
    cout << "子线程: " << this_thread::get_id() << endl;
}

int main()
{
    cout << "主线程: " << this_thread::get_id() << endl;
    thread t(func);
    t.join();
}
程序启动，开始执行main()函数，此时只有一个线程也就是主线程。当创建了子线程对象t之后，指定的函数func()会在子线程中执行，这时通过调用this_thread::get_id()就可以得到当前线程的线程ID了。

2. sleep_for()
进程被创建后一共有五种状态
同样地线程被创建后也有这五种状态：创建态，就绪态，运行态，阻塞态(挂起态)，退出态(终止态) ，关于状态之间的转换是一样的，请参考进程，在此不再过多的赘述。

线程和进程的执行有很多相似之处，在计算机中启动的多个线程都需要占用CPU资源，但是CPU的个数是有限的并且每个CPU在同一时间点不能同时处理多个任务。为了能够实现并发处理，多个线程都是分时复用CPU时间片，快速的交替处理各个线程中的任务。因此多个线程之间需要争抢CPU时间片，抢到了就执行，抢不到则无法执行（因为默认所有的线程优先级都相同，内核也会从中调度，不会出现某个线程永远抢不到CPU时间片的情况）。

命名空间this_thread中提供了一个休眠函数sleep_for()，调用这个函数的线程会马上从运行态变成阻塞态并在这种状态下休眠一定的时长，因为阻塞态的线程已经让出了CPU资源，代码也不会被执行，所以线程休眠过程中对CPU来说没有任何负担。这个函数是函数原型如下，参数需要指定一个休眠时长，是一个时间段：

chrono库中的时间段类 duration 的使用
C++
1
2
template <class Rep, class Period>
  void sleep_for (const chrono::duration<Rep,Period>& rel_time);
示例程序如下：

C++
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void func()
{
    for (int i = 0; i < 10; ++i)
    {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "子线程: " << this_thread::get_id() << ", i = " << i << endl;
    }
}

int main()
{
    thread t(func);
    t.join();
}
在func()函数的for循环中使用了this_thread::sleep_for(chrono::seconds(1));之后，每循环一次程序都会阻塞1秒钟，也就是说每隔1秒才会进行一次输出。需要注意的是：程序休眠完成之后，会从阻塞态重新变成就绪态，就绪态的线程需要再次争抢CPU时间片，抢到之后才会变成运行态，这时候程序才会继续向下运行。

3. sleep_until()
命名空间this_thread中提供了另一个休眠函数sleep_until()，和sleep_for()不同的是它的参数类型不一样

sleep_until()：指定线程阻塞到某一个指定的时间点time_point类型，之后解除阻塞
sleep_for()：指定线程阻塞一定的时间长度duration 类型，之后解除阻塞
chrono库中的时间点类 time_point 的使用
该函数的函数原型如下：

C++
1
2
template <class Clock, class Duration>
  void sleep_until (const chrono::time_point<Clock,Duration>& abs_time);
示例程序如下：

C++

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void func()
{
    for (int i = 0; i < 10; ++i)
    {
        // 获取当前系统时间点
        auto now = chrono::system_clock::now();
        // 时间间隔为2s
        chrono::seconds sec(2);
        // 当前时间点之后休眠两秒
        this_thread::sleep_until(now + sec);
        cout << "子线程: " << this_thread::get_id() << ", i = " << i << endl;
    }
}

int main()
{
    thread t(func);
    t.join();
}
sleep_until()和sleep_for()函数的功能是一样的，只不过前者是基于时间点去阻塞线程，后者是基于时间段去阻塞线程，项目开发过程中根据实际情况选择最优的解决方案即可。

4. yield()
命名空间this_thread中提供了一个非常绅士的函数yield()，在线程中调用这个函数之后，处于运行态的线程会主动让出自己已经抢到的CPU时间片，最终变为就绪态，这样其它的线程就有更大的概率能够抢到CPU时间片了。使用这个函数的时候需要注意一点，线程调用了yield()之后会主动放弃CPU资源，但是这个变为就绪态的线程会马上参与到下一轮CPU的抢夺战中，不排除它能继续抢到CPU时间片的情况，这是概率问题。

C++
1
void yield() noexcept;
函数对应的示例程序如下：

C++

#include <iostream>
#include <thread>
using namespace std;

void func()
{
    for (int i = 0; i < 100000000000; ++i)
    {
        cout << "子线程: " << this_thread::get_id() << ", i = " << i << endl;
        this_thread::yield();
    }
}

int main()
{
    thread t(func);
    thread t1(func);
    t.join();
    t1.join();
}
在上面的程序中，执行func()中的for循环会占用大量的时间，在极端情况下，如果当前线程占用CPU资源不释放就会导致其他线程中的任务无法被处理，或者该线程每次都能抢到CPU时间片，导致其他线程中的任务没有机会被执行。解决方案就是每执行一次循环，让该线程主动放弃CPU资源，重新和其他线程再次抢夺CPU时间片，如果其他线程抢到了CPU时间片就可以执行相应的任务了。

结论：

std::this_thread::yield() 的目的是避免一个线程长时间占用CPU资源，从而导致多线程处理性能下降
std::this_thread::yield() 是让当前线程主动放弃了当前自己抢到的CPU资源，但是在下一轮还会继续抢
```
========================================================================
```C++
在上面的示例程序中有一个bug，在主线程中依次创建出两个子线程，打印两个子线程的线程ID，最后主线程执行完毕就退出了（主线程就是执行main()函数的那个线程）。默认情况下，主线程销毁时会将与其关联的两个子线程也一并销毁，但是这时有可能子线程中的任务还没有执行完毕，最后也就得不到我们想要的结果了。

当启动了一个线程（创建了一个thread对象）之后，在这个线程结束的时候（std::terminate()），我们如何去回收线程所使用的资源呢？thread库给我们两种选择：

加入式（join()）
分离式（detach()）
另外，我们必须要在线程对象销毁之前在二者之间作出选择，否则程序运行期间就会有bug产生。

2.2 join()
join()字面意思是连接一个线程，意味着主动地等待线程的终止（线程阻塞）。在某个线程中通过子线程对象调用join()函数，调用这个函数的线程被阻塞，但是子线程对象中的任务函数会继续执行，当任务执行完毕之后join()会清理当前子线程中的相关资源然后返回，同时，调用该函数的线程解除阻塞继续向下执行。

再次强调，我们一定要搞清楚这个函数阻塞的是哪一个线程，函数在哪个线程中被执行，那么函数就阻塞哪个线程。该函数的函数原型如下：

C++
1
void join();
有了这样一个线程阻塞函数之后，就可以解决在上面测试程序中的bug了，如果要阻塞主线程的执行，只需要在主线程中通过子线程对象调用这个方法即可，当调用这个方法的子线程对象中的任务函数执行完毕之后，主线程的阻塞也就随之解除了。修改之后的示例代码如下：

C++

int main()
{
    cout << "主线程的线程ID: " << this_thread::get_id() << endl;
    thread t(func, 520, "i love you");
    thread t1(func1);
    cout << "线程t 的线程ID: " << t.get_id() << endl;
    cout << "线程t1的线程ID: " << t1.get_id() << endl;
    t.join();
    t1.join();
}
当主线程运行到第八行t.join();，根据子线程对象t的任务函数func()的执行情况，主线程会做如下处理：

如果任务函数func()还没执行完毕，主线程阻塞，直到任务执行完毕，主线程解除阻塞，继续向下运行
如果任务函数func()已经执行完毕，主线程不会阻塞，继续向下运行
同样，第9行的代码亦如此。

为了更好的理解join()的使用，再来给大家举一个例子，场景如下：

程序中一共有三个线程，其中两个子线程负责分段下载同一个文件，下载完毕之后，由主线程对这个文件进行下一步处理，那么示例程序就应该这么写：

C++
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void download1()
{
    // 模拟下载, 总共耗时500ms，阻塞线程500ms
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "子线程1: " << this_thread::get_id() << ", 找到历史正文...." << endl;
}

void download2()
{
    // 模拟下载, 总共耗时300ms，阻塞线程300ms
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "子线程2: " << this_thread::get_id() << ", 找到历史正文...." << endl;
}

void doSomething()
{
    cout << "集齐历史正文, 呼叫罗宾...." << endl;
    cout << "历史正文解析中...." << endl;
    cout << "起航，前往拉夫德尔...." << endl;
    cout << "找到OnePiece, 成为海贼王, 哈哈哈!!!" << endl;
    cout << "若干年后，草帽全员卒...." << endl;
    cout << "大海贼时代再次被开启...." << endl;
}

int main()
{
    thread t1(download1);
    thread t2(download2);
    // 阻塞主线程，等待所有子线程任务执行完毕再继续向下执行
    t1.join();
    t2.join();
    doSomething();
}
示例程序输出的结果：

C++
子线程2: 72540, 找到历史正文....
子线程1: 79776, 找到历史正文....
集齐历史正文, 呼叫罗宾....
历史正文解析中....
起航，前往拉夫德尔....
找到OnePiece, 成为海贼王, 哈哈哈!!!
若干年后，草帽全员卒....
大海贼时代再次被开启....
在上面示例程序中最核心的处理是在主线程调用doSomething();之前在第35、36行通过子线程对象调用了join()方法，这样就能够保证两个子线程的任务都执行完毕了，也就是文件内容已经全部下载完成，主线程再对文件进行后续处理，如果子线程的文件没有下载完毕，主线程就去处理文件，很显然从逻辑上讲是有问题的。

基于命名空间 this_thread 让当前线程休眠
2.3 detach()
detach()函数的作用是进行线程分离，分离主线程和创建出的子线程。在线程分离之后，主线程退出也会一并销毁创建出的所有子线程，在主线程退出之前，它可以脱离主线程继续独立的运行，任务执行完毕之后，这个子线程会自动释放自己占用的系统资源。（其实就是孩子翅膀硬了，和家里断绝关系，自己外出闯荡了，如果家里被诛九族还是会受牵连）。该函数函数原型如下：

C++
1
void detach();
线程分离函数没有参数也没有返回值，只需要在线程成功之后，通过线程对象调用该函数即可，继续将上面的测试程序修改一下：

C++
int main()
{
    cout << "主线程的线程ID: " << this_thread::get_id() << endl;
    thread t(func, 520, "i love you");
    thread t1(func1);
    cout << "线程t 的线程ID: " << t.get_id() << endl;
    cout << "线程t1的线程ID: " << t1.get_id() << endl;
    t.detach();
    t1.detach();
    // 让主线程休眠, 等待子线程执行完毕
    this_thread::sleep_for(chrono::seconds(5));
}
注意事项：线程分离函数detach()不会阻塞线程，子线程和主线程分离之后，在主线程中就不能再对这个子线程做任何控制了，比如：通过join()阻塞主线程等待子线程中的任务执行完毕，或者调用get_id()获取子线程的线程ID。有利就有弊，鱼和熊掌不可兼得，建议使用join()。

2.5 joinable()
joinable()函数用于判断主线程和子线程是否处理关联（连接）状态，一般情况下，二者之间的关系处于关联状态，该函数返回一个布尔类型：

返回值为true：主线程和子线程之间有关联（连接）关系
返回值为false：主线程和子线程之间没有关联（连接）关系
C++
1
bool joinable() const noexcept;
示例代码如下：

C++
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void foo()
{
    this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    thread t;
    cout << "before starting, joinable: " << t.joinable() << endl;

    t = thread(foo);
    cout << "after starting, joinable: " << t.joinable() << endl;

    t.join();
    cout << "after joining, joinable: " << t.joinable() << endl;

    thread t1(foo);
    cout << "after starting, joinable: " << t1.joinable() << endl;
    t1.detach();
    cout << "after detaching, joinable: " << t1.joinable() << endl;
}
示例代码打印的结果如下：

C++
before starting, joinable: 0
after starting, joinable: 1
after joining, joinable: 0
after starting, joinable: 1
after detaching, joinable: 0
基于示例代码打印的结果可以得到以下结论：

在创建的子线程对象的时候，如果没有指定任务函数，那么子线程不会启动，主线程和这个子线程也不会进行连接
在创建的子线程对象的时候，如果指定了任务函数，子线程启动并执行任务，主线程和这个子线程自动连接成功
子线程调用了detach()函数之后，父子线程分离，同时二者的连接断开，调用joinable()返回false
在子线程调用了join()函数，子线程中的任务函数继续执行，直到任务处理完毕，这时join()会清理（回收）当前子线程的相关资源，所以这个子线程和主线程的连接也就断开了，因此，调用join()之后再调用joinable()会返回false。
2.6 operator=
线程中的资源是不能被复制的，因此通过=操作符进行赋值操作最终并不会得到两个完全相同的对象。

C++

// move (1)	
thread& operator= (thread&& other) noexcept;
// copy [deleted] (2)	
thread& operator= (const other&) = delete;
通过以上=操作符的重载声明可以得知：

如果other是一个右值，会进行资源所有权的转移
如果other不是右值，禁止拷贝，该函数被显示删除（=delete），不可用
3. 静态函数
thread线程类还提供了一个静态方法，用于获取当前计算机的CPU核心数，根据这个结果在程序中创建出数量相等的线程，每个线程独自占有一个CPU核心，这些线程就不用分时复用CPU时间片，此时程序的并发效率是最高的。

C++
1
static unsigned hardware_concurrency() noexcept;
示例代码如下：

C++

#include <iostream>
#include <thread>
using namespace std;

int main()
{
    int num = thread::hardware_concurrency();
    cout << "CPU number: " << num << endl;
}
4. C线程库
C语言提供的线程库不论在window还是Linux操作系统中都是可以使用的，看明白了这些C语言中的线程函数之后会发现它和上面的C++线程类使用很类似（其实就是基于面向对象的思想进行了封装），但C++的线程类用起来更简单一些，链接奉上，感兴趣的可以一看。

