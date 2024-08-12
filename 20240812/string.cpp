/*
    show how to 封装一个基本的 string 类
    这个类实现了可变长度的字符串，内部自动管理内存，支持追加操作。
    它使用了动态内存分配，封装了基本的字符串操作，并且确保了内存的正确管理。
*/

#include <iostream>
#include <cstring> // For strlen, strcpy, strcat, etc.

class String
{
public:
    // 默认构造函数
    String() : data(nullptr), length(0), capacity(0) {}

    // 构造函数: 从C风格字符串初始化
    String(const char* str)
    {
        length = strlen(str);
        capacity = length + 1;// 多一个空间存储'\0'
        data = new char[capacity];
        std::strcpy(data, str);// 复制字符串
    }

    // 拷贝构造函数
    String(const String& other)
    {
        length = other.length;// 长度
        capacity = other.capacity;// 
        data = new char[capacity];// 分配内存
        std::strcpy(data, other.data);// 复制字符串
    }

    // 移动构造函数--为了避免不必要的资源复制，通过转移资源的所有权来减少内存分配和复制操作的开销。
    // 它接受一个右值引用（String&&）作为参数。右值引用允许函数接收临时对象或即将被销毁的对象，从而可以安全地“窃取”这些对象的资源。
    // noexcept 表示这个函数不会抛出异常
    String(String&& other) noexcept
        : data(other.data), length(other.length), capacity(other.capacity)
    // 通过初始化列表将 other 对象的内部资源（如指针、长度和容量）直接转移到新创建的对象中。
    // 这一行直接将资源的所有权从 other 转移到当前对象，而不进行任何数据的复制。
    {
        /*
            在转移完成后，将 other 的指针 data 置为空指针，并将 length 和 capacity 置为 0。这样做是为了将 other 对象重置为一个有效但空的状态，
            避免在 other 被析构时试图释放原来的资源（因为这些资源的所有权已经转移到新对象中了）。
        */
        other.data = nullptr;
        other.length = 0;
        other.capacity = 0;
    }

    // 析构函数
    ~String()
    {
        delete[] data;
    }

    // 拷贝赋值运算符
    String& operator=(const String& other)
    {
        if(this != &other)// 避免自赋值
        {
            delete[] data;// 释放当前对象的内存
            length = other.length;
            capacity = other.capacity;
            data = new char[capacity];
            std::strcpy(data, other.data);// 复制字符串
        }
        return *this;
    }

    // 移动赋值运算符
    String& operator=(String&& other) noexcept
    {
        if(this != &other)
        {
            delete[] data;// 释放当前对象的内存
            data = other.data;
            length = other.length;
            capacity = other.capacity;
            other.data = nullptr;// 将 other 对象重置为空状态
            other.length = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 追加操作
    void push_back(char ch)
    {
        if(length + 1 >= capacity)
        {
            resize(capacity * 2);
        }
        data[length++] = ch;
        data[length] = '\0';// 确保字符串以空字符结尾
    }

    // 追加字符串
    void append(const char* str)
    {
        size_t str_len = std::strlen(str);// 获取字符串的长度
        if(length + str_len >= capacity)// 如果当前容量不足以容纳新字符串
        {
            resize(length + str_len + 1);// 调整容量
            // length：表示当前字符串的实际长度，即字符串中有效字符的数量（不包括末尾的空字符 \0）。

// capacity：表示当前为字符串分配的内存容量，即 data 数组的大小。它包含 length 所表示的字符数量和额外的可用空间。
        }
        std::strcat(data, str);
        length += str_len;// 更新
    }

    // 获取字符串长度
    size_t size() const
    {
        return length;
    }

    // 获取C字符串
    const char* c_str() const
    {
        return data;
    }


private:
    char *data;
    size_t length;// 长度
    size_t capacity;// 容量

    // 调整内容大小的方法->以便容纳更多的字符-- 设置为私有不可被外部访问
    void resize(size_t new_capacity)// 新的容量
    {
        char *new_data = new char[new_capacity];// 为存储新的字符串内容分配足够的内存
        if(data)// 检查是否已经有旧数据
        {
            // 保留原有字符串内容，并将其迁移到新分配的内存块中。
            std::strcpy(new_data, data);// 确保只有在有旧数据时才进行复制和释放操作
            delete[] data;// 释放原有内存块
        }
        data = new_data;// 更新指向新内存块的指针
        capacity = new_capacity;// 更新容量
    }

};

int main(int argc, char *argv[])
{
    String s("hello");
    std::cout << "Initial string: " << s.c_str() << std::endl;

    s.push_back(' ');
    s.append("world!");

    std::cout << "After appending: " << s.c_str() << std::endl;


    return 0;
}

