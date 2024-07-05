
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}/include/thrift
        ${CMAKE_BINARY_DIR}/include
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")


# 将源代码添加到此项目的可执行文件。
# add_executable (demoX main.cpp)
# add_executable (ios_service_strand ios_service_strand.cpp)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--as-needed")

# target_link_options(demoX PRIVATE "--as-needed")
# target_link_options(demoX PRIVATE "-Wl")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -pg")
# target_link_options(demoX PRIVATE "-pg")
# target_link_libraries(demoX ${ALL_STATIC_LIBS} pthread)
# target_link_libraries(ios_service_strand ${ALL_STATIC_LIBS} pthread)

# set(MyTestCaseFiles
#     main.cpp
#     another_file.cpp
# )

# file(GLOB MyTestCaseFiles *.cpp)
# foreach(SOURCE_FILE ${MyTestCaseFiles})
#     get_filename_component(FILE_NAME_WE ${MyTestCaseFiles} NAME_WE)
#     add_executable(${FILE_NAME_WE} ${MyTestCaseFiles})
# endforeach()

set( SRC_FILES
    main.cpp
    ios_service_strand.cpp
    scop_guard.cpp
    eigen_test.cpp
)

# 遍历源文件列表
foreach(SOURCE_FILE ${SRC_FILES})
#     add_dependencies(demoX libboost libtcmalloc  )

    # 提取文件名（不包含扩展名）
    get_filename_component(FILE_NAME_WE ${SOURCE_FILE} NAME_WE)
    
    # 根据文件名创建可执行文件
    add_executable(${FILE_NAME_WE} ${SOURCE_FILE})
    target_link_libraries(${FILE_NAME_WE} ${ALL_STATIC_LIBS} pthread)
    target_link_libraries(${FILE_NAME_WE} ${ALL_STATIC_LIBS} pthread)

endforeach()
# target_link_libraries(demoX libtcmalloc.a  libprofiler.a libboost_system.a libboost_thread.a  pthread )
