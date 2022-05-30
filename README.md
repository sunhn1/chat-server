# chat-server
基于muduo库开发的集群聊天服务器和客户端源码，可以工作在nginx tcp负载均衡环境中，使用mysql数据库，运用了json的序列化和反序列化
编译方式：cd build
rm -rf *
cmake ..
make

运行：
需要nginx的TCP负载均衡
redis消息队列进行不同服务器之间的通信

bin目录：存放可执行文件
include目录：存放头文件
src目录：存放源文件
build目录：存放编译过程中产生的临时中间文件
thridpatry:第三方库文件
