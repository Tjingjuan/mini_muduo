//
// Created by Jingjuan on 2020/8/9.
//

#include "TcpServer.h"

void TcpServer::newConnection(int sockfd) {
    TcpConnection* tcp = new TcpConnection(sockfd,loop_); // Memory Leak !!!
    connections_[sockfd] = tcp;
    tcp->setUser(pUser_);
    tcp->connectEstablished();
}

TcpServer::TcpServer(EventLoop *loop)
    :pAcceptor_(nullptr)
    ,loop_(loop)
    ,pUser_(nullptr){
}

void TcpServer::start() {
    pAcceptor_ = new Accept(loop_); // Memory Leak !!!
    pAcceptor_->setCallBack(this);
    pAcceptor_->start();
}

void TcpServer::setCallback(IMuduoUser *pUser) {
    pUser_ = pUser;
}