cmake_minimum_required(VERSION 3.6)
project(lieventModel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/)
set(SOURCE_FILES main.cpp)
add_executable(lieventModel ${SOURCE_FILES})
target_link_libraries(lieventModel ${CMAKE_SOURCE_DIR}/lib/libevent.so)