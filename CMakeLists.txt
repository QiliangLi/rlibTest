project (rlib)

cmake_minimum_required(VERSION 2.8)

## use C++11 features
add_definitions(-std=c++11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# file(GLOB SOURCES "*.hpp")
file(GLOB SOURCES "*.hpp" "*.h" "*.cc")

add_library(rdma STATIC ${SOURCES})
set_target_properties(rdma PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(rdma -lpthread ibverbs)

add_executable(server "example/server.cpp")
add_executable(read_client "example/read/client.cpp")
add_executable(write_client "example/write/client.cpp")
add_executable(cas_client "example/cas/client.cpp")
add_executable(faa_client "example/faa/client.cpp")
add_executable(lrBatch_client "example/lr_batch/client.cpp")
add_executable(lwBatch_client "example/lw_batch/client.cpp")
add_executable(llBatch_client "example/ll_batch/client.cpp")

target_link_libraries(server rdma)
target_link_libraries(read_client rdma)
target_link_libraries(write_client rdma)
target_link_libraries(cas_client rdma)
target_link_libraries(faa_client rdma)
target_link_libraries(lrBatch_client rdma)
target_link_libraries(lwBatch_client rdma)
target_link_libraries(llBatch_client rdma)

