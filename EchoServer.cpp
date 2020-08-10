//
// Created by Jingjuan on 2020/8/10.
//

#include "EchoServer.h"

EchoServer::EchoServer(EventLoop *pLoop)
    :ploop_(pLoop),tcpServer_(pLoop) {
    tcpServer_.setCallback(this);
}

void EchoServer::start() {
    tcpServer_.start();
}

void EchoServer::onConnection(TcpConnection *pConn) {
    cout<<" onConnection"<<endl;
}

void EchoServer::onMessage(TcpConnection *pConn, const string &data) {
    cout<<"onmessage"<<endl;
    pConn->send(data);
}