#ifndef CHATSERVER_H
#define CHATSERVER_H

#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
using namespace muduo::net;
using namespace muduo;
//聊天服务器的主类
class ChatServer{
    
    public:
        //初始化聊天服务器对象
        ChatServer(EventLoop* loop,//事件循环
            const InetAddress& listenAddr,//Ip+端口
            const string& nameArg);//服务器名称
        //启动服务
        void start();
    private:
        //上报用户创建和断开相关的回调函数
        void onConnection(const TcpConnectionPtr&);
        //专门处理用户的读写事件 的回调函数
        void onMessage(const TcpConnectionPtr &,//连接
                            Buffer*,//缓冲区
                            Timestamp);
        TcpServer _server;//组合muduo库实现服务器功能的类对象
        EventLoop *_loop;//指向事件循环的指针
};

#endif 