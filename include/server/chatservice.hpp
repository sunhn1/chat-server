#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "json.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "redis.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

// JSON的消息回调 处理消息事件的方法回调类型 这是一个类型，是处理事件的方法的类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json *js, Timestamp)>;

class ChatService
{
public:
    //获取单例对象的接口函数
    static ChatService *instance();
    //处理登录业务
    void login(const TcpConnectionPtr &conn, json *js, Timestamp time);
    //处理注册业务
    void reg(const TcpConnectionPtr &conn, json *js, Timestamp time);
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json *js, Timestamp time);
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json *js, Timestamp time);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json *js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json *js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json *js, Timestamp time);
    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    // 服务器异常，业务重置方法
    void reset();
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json *js, Timestamp time);
    // 从redis消息队列中获取订阅的消息，由redis调用
    void handleRedisSubscribeMessage(int, string);

private:
    //构造函数私有化
    ChatService();
    // 存储消息id和其对应的业务处理方法 也就是一个消息id对应一个函数方法 如1对应用户注册函数  绑定起来
    unordered_map<int, MsgHandler> _msgHandlerMap;
    // 数据操作类对象
    UserModel _userModel;
    // 存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;
    //定义一把互斥锁，解决线程安全问题
    mutex _connMutex;
    //离线消息对象
    OfflineMsgModel _offlineMsgModel;
    //好友列表操作对象
    FriendModel _friendModel;
    //群组对象
    GroupModel _groupModel;

    // redis操作对象
    Redis _redis;
};
#endif