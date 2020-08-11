//
// Created by Jingjuan on 2020/8/10.
//

#ifndef MINI_MUDUO_TCPCONNECTION_H
#define MINI_MUDUO_TCPCONNECTION_H
#include "Channel.h"
#include "IMuduoUser.h"
#include <iostream>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 100
#define MAX_EVENT 500
using namespace std;
//class IAcceptorCallBack;

class TcpConnection: public IChannelCallBack{
public:
public:
    TcpConnection(int sockfd,EventLoop* loop);
    ~TcpConnection(){}
    void send(const string& message);
    void connectEstablished();
//    void setCallback(IAcceptorCallBack* pCallback);
    void setUser(IMuduoUser* pUser);
    void handleRead();
    void handleWrite();
private:
    int sockfd_;
    EventLoop* loop_;
    Channel* pChannel_;
    IMuduoUser* pUser_;
    string* inBuf_;  //写缓冲区
    string* outBuf_;  //读缓冲区
};


#endif //MINI_MUDUO_TCPCONNECTION_H
