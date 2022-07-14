project (rlib)

cmake_minimum_required(VERSION 2.8)

## use C++11 features
add_definitions(-std=c++11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

file(GLOB SOURCES "*.hpp")

add_library(rdma STATIC ${SOURCES})
set_target_properties(rdma PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(rdma -lpthread ibverbs)

add_executable(server "example/read/server.cpp")
add_executable(client "example/read/client.cpp")

target_link_libraries(server rdma)
target_link_libraries(client rdma)