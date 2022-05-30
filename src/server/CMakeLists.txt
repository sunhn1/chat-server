#定义一个SRC_LIST变量，吧所有源文件放入
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)
#指定生成可执行文件
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})
#可执行文件位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#目标程序需要链接muduo_net muduo_base pthread这三个库文件,生成chatserver模板可执行文件
target_link_libraries(ChatServer muduo_net muduo_base mysqlclient hiredis pthread )