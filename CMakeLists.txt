cmake_minimum_required(VERSION 3.10) # 

project(MyProject)

include(3rd.cmake)

# 添加你的可执行文件或其他目标
add_executable(MyExecutable main.cpp)

target_link_libraries(MyExecutable ${Boost_LIBRARIES})  