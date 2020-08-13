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

void EchoServer::onMessage(TcpConnection *pConn, Buffer* pBuf) {
    cout<<"onmessage"<<endl;
    int i = 0;
    while(pBuf->readableBytes() > MESSAE_LENTH){
        string  message = pBuf->retrieveAsString(MESSAE_LENTH);
        cout<<i++<<":"<<message<<endl;
        pConn->send(message+"\n");
    }
    if(pBuf->readableBytes() >0){
        string  message = pBuf->retrieveAsString(pBuf->readableBytes());
        cout<<i++<<":"<<message<<endl;
        pConn->send(message+"\n");
    }
}
void EchoServer::onWriteComplate(TcpConnection* pCon)
{
    cout << "onWriteComplate" << endl;
}