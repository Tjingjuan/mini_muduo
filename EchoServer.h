//
// Created by Jingjuan on 2020/8/10.
//

#ifndef MINI_MUDUO_ECHOSERVER_H
#define MINI_MUDUO_ECHOSERVER_H
#include "TcpServer.h"
#include "IMuduoUser.h"
#include "Buffer.h"

class EchoServer: public IMuduoUser {
public:
    EchoServer(EventLoop* pLoop);
    ~EchoServer(){}
    void start();
    void virtual onConnection(TcpConnection* pConn);
    void virtual onMessage(TcpConnection* pConn, Buffer* pBuf);
    void virtual onWriteComplate(TcpConnection* pCon);

private:
    EventLoop *ploop_;
    TcpServer tcpServer_;
};


#endif //MINI_MUDUO_ECHOSERVER_H
