
# add_subdirectory(thrift)
# add_subdirectory(protobuf)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}/include/thrift
)

# 将源代码添加到此项目的可执行文件。
add_executable (demo1 main.cpp)

add_dependencies(demo1
		libboost
		# gen_client_protocol
		# gen_server_protocol
        )

# target_link_libraries(demo1
# 		#YYService
# 		# ServiceGateClient
# 		# # eduFrame
# 		# libthrift.a
# 		# libmetrics.a
# 		# libp2cache.a
#         # libprotobuf.a
# 		# libcrypto.a
# 		pthread
# 		rt
#         )