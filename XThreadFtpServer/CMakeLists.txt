cmake_minimum_required(VERSION 3.6)
project(XThreadFtpServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -lpthread ")


set(SOURCE_FILES main.cpp XThreadPool.cpp XThread.cpp XFtpServercCMD.cpp XFtpFactory.cpp XFtpTask.cpp XFtpUSER.cpp XFtpList.cpp ThreadPool/XFtpList.h XFtpPORT.cpp ThreadPool/XFtpPORT.h XFtpRETR.cpp ThreadPool/XFtpRETR.h)
add_executable(XThreadFtpServer ${SOURCE_FILES})
target_link_libraries(XThreadFtpServer ${CMAKE_SOURCE_DIR}/lib/libevent.so)