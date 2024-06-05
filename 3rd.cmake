include(ExternalProject)
#配置需要编译的boost所用的库
set(BUILD_BOOST_LIBS "filesystem,program_options,stacktrace,test")

ExternalProject_Add(libboost
        EXCLUDE_FROM_ALL 1
        URL ${PROJECT_SOURCE_DIR}/tar/boost_1_67_0.tar.gz
        CONFIGURE_COMMAND ./bootstrap.sh --with-libraries=${BUILD_BOOST_LIBS}
        BUILD_IN_SOURCE 1
        BUILD_COMMAND ""
        INSTALL_COMMAND ./b2 cxxflags="-std=c++11" link=static install --prefix=${PROJECT_BINARY_DIR}
        )

# ExternalProject_Add(libtcmalloc
#         EXCLUDE_FROM_ALL 1
#         URL ${PROJECT_SOURCE_DIR}/tar/gperftools-2.7.tar.gz
#         CONFIGURE_COMMAND ./configure --prefix=${PROJECT_BINARY_DIR} --enable-shared=no --disable-cpu-profiler --disable-heap-profiler --disable-heap-checker --disable-debugalloc --enable-minimal
#         BUILD_IN_SOURCE 1
#         BUILD_COMMAND make
#         INSTALL_COMMAND make install
#         )

# ExternalProject_Add(libhiredis
#         EXCLUDE_FROM_ALL 1
#         URL ${PROJECT_SOURCE_DIR}/tar/hiredis-0.13.3.tar.gz
#         CONFIGURE_COMMAND ""
#         BUILD_IN_SOURCE 1
#         BUILD_COMMAND make
#         INSTALL_COMMAND make PREFIX=${PROJECT_BINARY_DIR} install
#         )


# ExternalProject_Add(libopenssl
#         EXCLUDE_FROM_ALL 1
#         URL ${PROJECT_SOURCE_DIR}/tar/openssl-1.0.2n.tar.gz
#         CONFIGURE_COMMAND ./config --prefix=${PROJECT_BINARY_DIR}
#         BUILD_IN_SOURCE 1
#         BUILD_COMMAND make
#         INSTALL_COMMAND make install
#         )

# ExternalProject_Add(libevent
#         EXCLUDE_FROM_ALL 1
#         URL ${PROJECT_SOURCE_DIR}/tar/libevent-2.0.22-stable.tar.gz
#         CONFIGURE_COMMAND ./configure --prefix=${PROJECT_BINARY_DIR}
#         BUILD_IN_SOURCE 1
#         BUILD_COMMAND make
#         INSTALL_COMMAND make install
#         )

# ExternalProject_Add(libthrift
#         EXCLUDE_FROM_ALL 1
#         DEPENDS libboost libopenssl libevent
#         URL ${PROJECT_SOURCE_DIR}/tar/thrift-0.11.0.tar.gz
#         CONFIGURE_COMMAND ./configure --prefix=${PROJECT_BINARY_DIR} --enable-shared=no --with-cpp --with-python=no --with-python3=no --with-ruby=no --with-boost=${PROJECT_BINARY_DIR} --with-openssl=${PROJECT_BINARY_DIR} --with-libevent=${PROJECT_BINARY_DIR}
#         BUILD_IN_SOURCE 1
#         BUILD_COMMAND make
#         INSTALL_COMMAND make install
#         )

# ExternalProject_Add(libjson
#         EXCLUDE_FROM_ALL 1
#         URL ${PROJECT_SOURCE_DIR}/tar/jsoncpp-1.8.4.tar.gz
#         CMAKE_COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release -DBUILD_STATIC_LIBS=ON -DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}
#         BUILD_COMMAND make
#         INSTALL_COMMAND make install
#         )

# ExternalProject_Add(libprotobuf
#         URL ${PROJECT_SOURCE_DIR}/tar/protobuf-cpp-3.6.1.tar.gz
#         CONFIGURE_COMMAND ./configure --prefix=${PROJECT_BINARY_DIR} --enable-shared=no
#         BUILD_IN_SOURCE 1
#         BUILD_COMMAND make
#         INSTALL_COMMAND make install
#         )


# ExternalProject_Add(libmetrics
#         EXCLUDE_FROM_ALL 1
#         URL ${PROJECT_SOURCE_DIR}/tar/metrics-2018.11.13-bin.tar.gz
#         CONFIGURE_COMMAND ""
#         BUILD_COMMAND ""
#         BUILD_IN_SOURCE 1
#         INSTALL_COMMAND cp -rf include ${PROJECT_BINARY_DIR} && cp -rf lib ${PROJECT_BINARY_DIR}
#         )

# #ExternalProject_Get_Property(libmetrics BINARY_DIR)
# #ExternalProject_Add_Step(libmetrics install_metrics
# #        DEPENDEES build
# #        COMMENT "install yy metrics"
# #        WORKING_DIRECTORY ${BINARY_DIR}
# #        COMMAND cp -r ${BINARY_DIR}/lib/libmetrics.a ${PROJECT_BINARY_DIR}/lib/
# #        COMMAND cp -r ${BINARY_DIR}/src/metrics_api.h ${PROJECT_BINARY_DIR}/include/
# #        )

# ExternalProject_Add(libp2cache
#         EXCLUDE_FROM_ALL 1
#         DEPENDS libboost libprotobuf
# #        GIT_REPOSITORY https://github.com/as-xjc/protobuf-l2cache
#         URL ${PROJECT_SOURCE_DIR}/tar/protobuf-l2cache-0.0.10.tar.gz
#         CMAKE_COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR} -DBOOST_DIR=${PROJECT_BINARY_DIR} -DPROTOBUF_DIR=${PROJECT_BINARY_DIR}
#         BUILD_COMMAND make
#         INSTALL_COMMAND make install
# )