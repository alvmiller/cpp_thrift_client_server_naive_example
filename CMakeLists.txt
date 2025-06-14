cmake_minimum_required(VERSION 3.5)
project(LoggerService)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Additional compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wno-deprecated-declarations")

include_directories(${CMAKE_SOURCE_DIR})
include_directories("/home/user1/apache/")
include_directories("/home/user1/apache/thrift/lib/cpp/src/")
link_directories("/home/user1/apache/thrift/lib/cpp/.libs")

set(BASE_SOURCE_FILES 
    gen-cpp/Logger.cpp 
    gen-cpp/LoggerService_types.cpp 
)

set(SERVER_FILES LoggerServer.cpp)
set(CLIENT_FILES LoggerClient.cpp)

add_executable(LoggerServer ${SERVER_FILES} ${BASE_SOURCE_FILES})
add_executable(LoggerClient ${CLIENT_FILES} ${BASE_SOURCE_FILES})
target_link_libraries(LoggerServer thrift)
target_link_libraries(LoggerClient thrift)
