cmake_minimum_required(VERSION 3.0)#>3.0版本以上
project(main)#工程名称
set(CMAKE_CXX_STANDARD 11)
#配置编译选项 可执行文件可以调试
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#配置头文件搜索路径
#include_directories()

#配置库文件搜索路径  默认有 暂不需要
#link_directories()

#设置需要编译的源文件列表
#set(SRC_LIST muduoserver.cpp)

# 还可以自动设置 所有的源文件列表 
# 把.指定路径下的所有文件名放入变量名SRC_LIST里面
aux_source_directory(. SRC_LIST)

#设置可执行文件最终存储的路径  bin目录下
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#则生成可执行文件可以这么写，表示生成的可执行文件server可由SRC_LIST变量所定义的源文件编译而来
add_executable(server ${SRC_LIST})

#生成可执行文件  如果只有一个文件 可以这么写可执行文件
#add_executable(server muduoserver.cpp)#server是名称 生成的可执行文件名称

#server这个目标程序需要链接muduo_net muduo_base pthread这三个库文件
target_link_libraries(server muduo_net muduo_base pthread)

