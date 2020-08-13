cmake_minimum_required(VERSION 3.5)
project(mini_muduo)

set(CMAKE_CXX_STANDARD 14)

add_executable(mini_muduo main.cpp TcpServer.cpp TcpServer.h Channel.cpp Channel.h Accept.cpp Accept.h TcpConnection.cpp TcpConnection.h EventLoop.cpp EventLoop.h Epoll.cpp Epoll.h EchoServer.cpp EchoServer.h IMuduoUser.h Buffer.cpp Buffer.h IRun.h IChannelCallBack.h)