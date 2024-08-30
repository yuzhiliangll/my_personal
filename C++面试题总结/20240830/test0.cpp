#include <iostream>
#include <mutex>
#include <atomic>

#if 0
class Singleton
{
public:
    static Singleton* getInstance()
    {
        if (instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(mutex);// 加锁
            if (instance == nullptr)
            {
                instance = new Singleton();// 创建实例
            }
        }
        return instance; //懒汉式
    }

    // 删除拷贝构造函数 和 赋值操作符
    Singleton(const Singleton&) = delete;// 删除拷贝构造函数
    Singleton& operator=(const Singleton&) = delete;//删除赋值操作符

private:
    Singleton() = default;
    static Singleton* instance;// 静态成员变量
    static std::mutex mutex;// 静态成员变量

};

Singleton* Singleton::instance = nullptr;// 静态成员变量初始化
std::mutex Singleton::mutex;// 静态成员变量初始化
#endif

#if 0
// 饿汉式
class Singleton
{
public:
    static Singleton* getInstance()
    {
        return &instance;// 饿汉式
    }

    // 删除拷贝构造函数 和 赋值操作符
    Singleton(const Singleton&) = delete;// 删除拷贝构造函数
    Singleton& operator=(const Singleton&) = delete;//删除赋值操作符

private:
    Singleton() = default;
    static Singleton instance;// 静态成员变量

};

Singleton Singleton::instance;// 静态成员变量初始化
#endif


/*
    单例模式要点:
    1. 构造函数 和 析构函数是私有的，不允许外部生成和释放对象
    2. 静态成员变量和静态返回单例的成员函数
    3. 禁用拷贝构造和赋值运算符
*/

// 懒汉式  线程安全-- 原子操作 + 互斥锁 + 内存屏障
class Singleton4
{
public:
    static Singleton4* GetInstance()
    {
        Singleton4* tmp = _instance.load(std::memory_order_relaxed);//  获取实例
        std::atomic_thread_fence(std::memory_order_acquire);// 内存屏障
        if (tmp == nullptr)
        {
            std::lock_guard<std::mutex> lock(mutex);// 加锁
            tmp = _instance.load(std::memory_order_relaxed);//  获取实例
            if (tmp == nullptr) // 双重检查
            {
                tmp = new Singleton4();// 创建实例
                std::atomic_thread_fence(std::memory_order_release);// 内存屏障
                _instance.store(tmp, std::memory_order_relaxed);// 存储实例
                atexit(Destructor);// 注册析构函数
            }
        }
        return tmp;// 返回实例
    }

private:
    static void Destructor()
    {
        Singleton4* tmp = _instance.load(std::memory_order_relaxed);// 获取实例
        if (tmp != nullptr)
        {
            delete tmp;// 释放实例
        }
    }

    Singleton4() = default;
    ~Singleton4()
    {
        std::cout << "Destructor" << std::endl;
    }

    Singleton4(const Singleton4&) = delete;// 删除拷贝构造函数
    Singleton4& operator=(const Singleton4&) = delete;//删除赋值操作符
    Singleton4(Singleton4&&) = delete;// 删除移动构造函数
    Singleton4& operator=(Singleton4&&) = delete;//删除移动赋值操作符

    static std::atomic<Singleton4*> _instance;// 静态成员变量
    static std::mutex mutex;// 静态成员变量

};
std::atomic<Singleton4*> Singleton4::_instance;// 静态成员变量初始化
std::mutex Singleton4::mutex;// 静态成员变量初始化


// 饿汉式 -- 静态局部变量具备线程安全性 延迟加载 内存正确释放
class Singleton5
{
public:
    static Singleton5* GetInstance()
    {
        static Singleton5 instance;// 静态成员变量初始化
        return &instance;// 饿汉式
    }

private:
    Singleton5() = default;
    ~Singleton5()
    {
        std::cout << "Destructor 5" << std::endl;
    }
    Singleton5(const Singleton5&) = delete;// 删除拷贝构造函数
    Singleton5& operator=(const Singleton5&) = delete;//删除赋值操作符
    Singleton5(Singleton5&&) = delete;// 删除移动构造函数
    Singleton5& operator=(Singleton5&&) = delete;//删除移动赋值操作符

};



// 版本6 模板类单例模式  模板类封装了单例要点


