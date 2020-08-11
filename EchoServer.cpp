//
// Created by Jingjuan on 2020/8/10.
//

#include "EchoServer.h"
#define MESSAE_LENTH 20


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

void EchoServer::onMessage(TcpConnection *pConn, string *data) {
    cout<<"onmessage"<<endl;
    int i = 0;
    while(data->size() > MESSAE_LENTH){
        string  message = data->substr(0,MESSAE_LENTH);
        cout<<i++<<":"<<message<<endl;
        *data = data->substr(MESSAE_LENTH,data->size());
        pConn->send(message+"\n");
    }
    if(data->size()>0){
        string  message = data->substr(0,data->size());
        cout<<i++<<":"<<message<<endl;
        *data = string();
        pConn->send(message+"\n");
    }
}