#include "json.hpp"
using json = nlohmann::json;

#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

void fun1(){
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["msg"]="hello";
    //把json数据对象 序列化 成 json数据字符串 数据序列化
    string sendBUf = js.dump();
    cout<<sendBUf.c_str()<<endl;
}
//json反序列化
string fun2(){
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["msg"]="hello";
    //把json数据对象 序列化 成 json数据字符串 数据序列化
    string sendBUf = js.dump();
    return sendBUf;
}
int main(){
     fun1();
    //cout << __cplusplus << endl;
    //反序列化，接收字符串，转为数据
    string recvBuf = fun2();
    json jsBuf =json::parse(recvBuf);
    cout<<jsBuf["msg"]<<endl;
    return 0;
}
{"msgid":2,"name":"zhangsan","password":"root"}
{"msgid":2,"name":"lisi","password":"123"}
{"msgid":1,"id":1,"password":"root"}
{"msgid":1,"id":3,"password":"123"}
{"msgid":5,"id":1,"from":"zhangsan","to":3,"msg":"hello"}
{"msgid":6,"id":3,"friendid":1}

string name =(*js)["name"];
    string pwd =(*js)["password]"];
    User user;
    user.setName(name);
    user.setPwd(pwd);
    //判断注册是否成功 而非在线状态
    bool state = _userModel.insert(user);
    if(state){
         // 注册成功
        json response;
        response["msgid"] = REG_MSG_ACK;
        //为0表示注册成功
        response["errno"] = 0;
        response["id"] = user.getId();
        conn->send(response.dump());
    }else{
        json response;
        response["msgid"]=REG_MSG_ACK;
        response["errno"]=1;
        response["errmsg"]="register error";
        conn->send(response.dump());
    }