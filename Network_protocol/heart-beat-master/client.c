#include <stdio.h>
#include "socket.h"
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
struct FdInfo
{
    int fd;
    int count;  // 记录有多少次没有收到服务器回复的心跳包数据
};

void* parseRecvMessage(void* arg)
{
    struct FdInfo* info = (struct FdInfo*)arg;
    while (1)
    {
        char* buffer;
        enum Type t;
        recvMessage(info->fd, &buffer, &t);
        if (buffer == NULL)
        {
            continue;
        }
        else
        {
            if (t == Heart)
            {
                printf("心跳包...%s\n", buffer);
                pthread_mutex_lock(&mutex);
                info->count = 0;
                pthread_mutex_unlock(&mutex);
            }
            else
            {
                printf("数据包: %s\n", buffer);
            }
            free(buffer);
        }
    }
    return NULL;
}

// 1. 发送心跳包数据
// 2. 检测心跳包, 看看能否收到服务器回复的数据
void* heartBeat(void* arg)
{
    struct FdInfo* info = (struct FdInfo*)arg;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        info->count++;    // 默认没收到服务器回复的心跳包数据
        printf("fd = %d, count = %d\n", info->fd, info->count);
        if (info->count > 5)
        {
            // 客户端和服务器断开了连接
            printf("客户端和服务器断开了连接...\n");
            close(info->fd);
            // 释放套接字资源, 退出客户端程序
            exit(0);
        }
        pthread_mutex_unlock(&mutex);
        sendMessage(info->fd, "hello", 5, Heart);
        sleep(3);
    }
    return NULL;
}

int main()
{
    struct FdInfo info;
    unsigned short port = 8888;
    const char* ip = "127.0.0.1";
    info.fd = initSocket();
    info.count = 0;
    connectToHost(info.fd, port, ip);

    pthread_mutex_init(&mutex, NULL);

    // 创建接收数据的子线程
    pthread_t pid;
    pthread_create(&pid, NULL, parseRecvMessage, &info);

    // 添加心跳包子线程
    pthread_t pid1;
    pthread_create(&pid1, NULL, heartBeat, &info);


    while (1)
    {
        const char* data = "你好, 大丙....";
        // 发送数据
        sendMessage(info.fd, data, strlen(data), Message);
        sleep(2);
    }

    pthread_join(pid, NULL);
    pthread_join(pid1, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}