# HeartBeat

#### 介绍
基于C语言和多线程实现了心跳包机制，以及解决了TCP通信过程中粘包的问题。

#### 编译说明

*** 客户端

gcc client.c socket.c -o client -lpthread

*** 服务器

gcc server.c socket.c clientlist.c -o server -lpthread

