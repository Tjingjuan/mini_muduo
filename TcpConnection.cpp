//
// Created by Jingjuan on 2020/8/10.
//

#include "TcpConnection.h"

TcpConnection::TcpConnection(int sockfd, EventLoop* loop)
        :sockfd_(sockfd),loop_(loop),pUser_(nullptr)
{
    pChannel_ = new Channel(loop_, sockfd_); // Memory Leak !!!
    pChannel_->setCallBack(this);
    pChannel_->enableReading();
}


void TcpConnection::OnIn(int sockfd) {
    cout<<"OnIn:TcpConnection:"<<sockfd<<endl;
    int readlength;
    char line[MAX_LINE];
    if(sockfd < 0)
    {
        cout << "EPOLLIN sockfd < 0 error " << endl;
        return;
    }
    bzero(line, MAX_LINE);
    if((readlength = read(sockfd, line, MAX_LINE)) < 0)
    {
        if(errno == ECONNRESET)
        {
            cout << "ECONNREST closed socket fd:" << sockfd << endl;
            close(sockfd);
        }
    }
    else if(readlength == 0)
    {
        cout << "read 0 closed socket fd:" << sockfd << endl;
        close(sockfd);
    }
    else
    {
        // 处理收到的数据,将字符串小写转换为大写
        for(int i=0;i<MAX_LINE;i++){
            line[i] = toupper(line[i]);
        }
        string buf(line,MAX_LINE);
        pUser_->onMessage(this,buf);
//        if(write(sockfd, line, readlength) != readlength)
//            cout << "error: not finished one time" << endl;
    }
}

void TcpConnection::send(const string &message) {
    int n = ::write(sockfd_, message.c_str(), message.size());
    if( n != static_cast<int>(message.size()))
        cout << "write error ! " << message.size() - n << "bytes left" << endl;
}

void TcpConnection::connectEstablished() {
    if(pUser_)
        pUser_->onConnection(this);
}

void TcpConnection::setUser(IMuduoUser *pUser) {
    pUser_ = pUser;
}
