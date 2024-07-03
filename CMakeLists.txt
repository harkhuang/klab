# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.9)
# add_definitions(_TEST_OPEN_= 1 )
project (klab VERSION 1.0.0 LANGUAGES CXX)

# add_compile_options(-g -o -pg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_SKIP_RPATH true)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bins)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__CMAKE_FILE__='\"$(notdir $(abspath $<))\"'")

include_directories(
        ${PROJECT_BINARY_DIR}/include
        ${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}
)

link_directories(
        ${PROJECT_BINARY_DIR}/lib
)

set(ALL_STATIC_LIBS)

# 将 "path/to/static_libs" 目录下所有的 .a 文件添加到 ALL_STATIC_LIBS 变量
file(GLOB ALL_STATIC_LIBS "${PROJECT_BINARY_DIR}/lib/*.a")

# 链接所有找到的静态库


include(3rd.cmake)

# 包含子项目。
add_subdirectory(src)
add_subdirectory(benchmark_case)
# add_subdirectory(server)
# add_subdirectory(test-client)
# add_subdirectory(tools)

