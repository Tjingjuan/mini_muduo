//
// Created by Jingjuan on 2020/8/10.
//

#include "Accept.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>


Accept::Accept(EventLoop *loop)
    :listenfd_(-1),
    loop_(loop),
    pAcceptChannel_(nullptr),
    pCallBack_(nullptr){
}

int Accept::createAndListen_() {
    int on = 1;
    listenfd_ = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr;
    fcntl(listenfd_,F_SETFD,O_NONBLOCK);
    setsockopt(listenfd_,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(ADDR_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(-1 == bind(listenfd_,(struct sockaddr *)&servaddr,sizeof(servaddr))){
        cout<<"bind error:"<<errno<<endl;
    }
    if(-1== listen(listenfd_,MAX_LISTENFD)){
        cout<<"listen error:"<<errno<<endl;
    }
    return listenfd_;
}

void Accept::setCallBack(IAcceptorCallBack *pCallBack) {
    pCallBack_ = pCallBack;
}

void Accept::start() {
    listenfd_ = createAndListen_();
    pAcceptChannel_ = new Channel(loop_, listenfd_); // Memory Leak !!!
    pAcceptChannel_->setCallBack(this);
    pAcceptChannel_->enableReading();
}

void Accept::handleRead() {
    cout<<"OnIn:Accept:"<<listenfd_<<endl;
    int connfd;
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    connfd = accept(listenfd_, (sockaddr*)&cliaddr, (socklen_t*)&clilen);
    if(connfd > 0)
    {
        cout << "new connection from "
             << "[" << inet_ntoa(cliaddr.sin_addr)
             << ":" << ntohs(cliaddr.sin_port) << "]"
             << " new socket fd:" << connfd
             << endl;
    }
    else
    {
        cout << "accept error, connfd:" << connfd
             << " errno:" << errno << endl;
    }
    fcntl(connfd, F_SETFL, O_NONBLOCK); //no-block io

    pCallBack_->newConnection(connfd);
}

void Accept::handleWrite() {

}