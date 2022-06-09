#指定版本
cmake_minimum_required(VERSION 3.16)
 
#指定工程名称
project(ObjectSerialization)
 
#设置变量的值
set(SRC ${PROJECT_SOURCE_DIR}/src/main.cpp 
		${PROJECT_SOURCE_DIR}/src/tinyxml2.cpp include/XML.h include/binary.h include/base64.h src/base64.cpp)
		
set(CMAKE_CXX_STANDARD 14)
 
#指定头文件位置
include_directories(${PROJECT_SOURCE_DIR}/include)
 
#指定可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
 
#生成可执行文件
add_executable(res ${SRC} include/XML.h include/binary.h include/base64.h src/base64.cpp)
