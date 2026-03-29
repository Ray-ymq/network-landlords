cmake_minimum_required(VERSION 3.24)
project(serialize)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
link_directories(/usr/local/lib)

# 取出当前目录中所有的源文件, 存储到一个变量中
aux_source_directory(./ SRC)
# 把源文件制作成静态库
add_library(serialize STATIC ${SRC})

target_include_directories(serialize PUBLIC /usr/local/include)
target_link_libraries(serialize PUBLIC /usr/local/lib/libprotobuf.so)