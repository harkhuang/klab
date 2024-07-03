
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}/include/thrift
        ${CMAKE_BINARY_DIR}/include
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3")
# 将源代码添加到此项目的可执行文件。
add_executable (case_1 case_1.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_dependencies(case_1 libboost libtcmalloc libbenchmark )

target_link_libraries(case_1
        libtcmalloc.a 
        libprofiler.a
        libbenchmark.a
        # libbenchmark_main.a
        pthread
        )




add_executable (demo demo.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_dependencies(demo libboost libtcmalloc libbenchmark )

target_link_libraries(demo
        libtcmalloc.a 
        libprofiler.a
        libbenchmark.a
        # libbenchmark_main.a
        pthread
        )
        