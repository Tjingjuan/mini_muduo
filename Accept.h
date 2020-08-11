//
// Created by Jingjuan on 2020/8/10.
//

#ifndef MINI_MUDUO_ACCEPT_H
#define MINI_MUDUO_ACCEPT_H

#include "Channel.h"
using namespace std;

#define ADDR_PORT 6666
#define MAX_LISTENFD 50

class IAcceptorCallBack
{
public:
    void virtual newConnection(int sockfd)=0;
};

class Accept: public IChannelCallBack{
public:
    Accept(EventLoop *loop);
    ~Accept(){}

    void virtual handleRead();
    void virtual handleWrite();
    void setCallBack(IAcceptorCallBack* pCallBack);
    void start();

private:
    int createAndListen_();
    EventLoop* loop_;
    int listenfd_;
    Channel* pAcceptChannel_;
    IAcceptorCallBack* pCallBack_;
};

#endif //MINI_MUDUO_ACCEPT_H
