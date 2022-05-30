/*muduo网络库给用户提供了两个主要的类
TcpServer:用于编写服务器程序
TcpClient：用于编写客户端程序

epoll+线程池
好处：把网络I/O代码和业务代码区分开
            写代码时只需要关注用户的连接和断开 用户的可读写事件
*/
#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<iostream>
#include<functional>//绑定器
#include<string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;//参数占位符
/*
1、组件TcpServer对象
2、创建eventloop事件循环对象指针
3、明确TcpServe构造函数需要什么参数 输出ChatServer构造函数
4、在当前服务器类的构造函数中注册处理连接的回调函数和处理读写事件的回调函数
5、muduo库是epoll+线程库  s设置合适的服务端线程数量 muduo库会自己划分I/O线程和worker线程
*/
class ChatServer{ 
public:
    ChatServer(EventLoop* loop,//事件循环
            const InetAddress& listenAddr,//Ip+端口
            const string& nameArg)//服务器名称
            :_server(loop, listenAddr, nameArg)
            ,_loop(loop)
            {
                //给服务器注册用户连接的创建和断开回调
                    /*  回调：普通函数是知道什么时间发生 发生之后执行什么任务
                        回调函数不清楚该事件什么时间发生，但知道发生后执行什么任务，用户的创建和断开都不清楚什么时间
                    发生，需要网络有消息了才会知道
                    */
                _server.setConnectionCallback(std::bind(&ChatServer::onConnection,this,_1));
                //给服务器注册用户读写事件的回调
                _server.setMessageCallback(std::bind(&ChatServer::onMessage,this,_1,_2,_3));//_1参数占位符
                //设置服务器的线程数量 1个IO线程  3个worker线程
                _server.setThreadNum(4);
            }
    //开启事件循环
    void start(){
        _server.start();
    }
private:
    //专门处理用户的创建和连接 epoll listenfd accept
    void onConnection(const TcpConnectionPtr& conn){
        if(conn->connected()){
            cout<<conn->peerAddress().toIpPort()<<"->"<< conn->localAddress().toIpPort()<<"state:online"<<endl;
        }else{
            cout<<conn->peerAddress().toIpPort()<<"->"<< conn->localAddress().toIpPort()<<"state:offline"<<endl;
        }
    }
    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn,//连接
                            Buffer* buffer,//缓冲区
                            Timestamp time)//接收到数据的时间信息
                            {
                                string buf =buffer->retrieveAllAsString();
                                cout<<"recv data:"<<buf<<"time:"<<time.toString()<<endl;
                                conn->send(buf);
                            }
    TcpServer _server;//muduo::net下的名称 #1
    EventLoop *_loop;//
};
int main(){
    EventLoop loop;
    InetAddress addr("127.0.0.1",6000);
    ChatServer server(&loop,addr,"ChatServer");
    server.start();
    loop.loop();
    return 0;
}