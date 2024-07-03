
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}/include/thrift
        ${CMAKE_BINARY_DIR}/include
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")


# 将源代码添加到此项目的可执行文件。
add_executable (demoX main.cpp)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--as-needed")

# target_link_options(demoX PRIVATE "--as-needed")
# target_link_options(demoX PRIVATE "-Wl")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -pg")
# target_link_options(demoX PRIVATE "-pg")
add_dependencies(demoX libboost libtcmalloc  )
# 创建一个变量来存储库列表

target_link_libraries(demoX ${ALL_STATIC_LIBS} pthread)
# target_link_libraries(demoX libtcmalloc.a  libprofiler.a libboost_system.a libboost_thread.a  pthread )
