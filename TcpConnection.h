//
// Created by Jingjuan on 2020/8/10.
//

#ifndef MINI_MUDUO_TCPCONNECTION_H
#define MINI_MUDUO_TCPCONNECTION_H
#include "Channel.h"
#include <iostream>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 100
#define MAX_EVENT 500
using namespace std;

class TcpConnection: public IChannelCallBack{
public:
public:
    TcpConnection(int sockfd,EventLoop* loop);
    ~TcpConnection(){}

    void virtual OnIn(int sockfd);
private:

    int sockfd_;
    EventLoop* loop_;
    Channel* pChannel_;
};


#endif //MINI_MUDUO_TCPCONNECTION_H
