//
// Created by Jingjuan on 2020/8/9.
//

#ifndef MINI_MUDUO_TCPSERVER_H
#define MINI_MUDUO_TCPSERVER_H

#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h> //for bzero
#include <iostream>
#include <unistd.h>
#include <vector>

#include <map>

#include "Channel.h"
#include "Accept.h"
#include "TcpConnection.h"
#include "IMuduoUser.h"

#define MAX_LINE 100
#define MAX_EVENT 500



using namespace std;

class TcpServer: public IAcceptorCallBack {
public:
    TcpServer(EventLoop* loop);
    ~TcpServer(){}
    void start();
    void setCallback(IMuduoUser* pUser);
    virtual void newConnection(int sockfd);
private:
//    void updata(Channel* pChannel,int op);
    EventLoop* loop_;
    struct epoll_event events_[MAX_EVENT];
    map<int,TcpConnection*> connections_;
    Accept* pAcceptor_;
    IMuduoUser* pUser_;
};


#endif //MINI_MUDUO_TCPSERVER_H
