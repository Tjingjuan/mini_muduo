//
// Created by Jingjuan on 2020/8/9.
//

#ifndef MINI_MUDUO_CHANNEL_H
#define MINI_MUDUO_CHANNEL_H
#include "EventLoop.h"
#include <sys/epoll.h>
#include <iostream>

class IChannelCallBack{
public:
//    void virtual OnIn(int sockfd)=0;
    void virtual handleWrite() = 0;
    void virtual handleRead() = 0;
};

class EventLoop;

class Channel
{
public:
    Channel(EventLoop* loop, int sockfd);
    ~Channel(){}
    void setCallBack(IChannelCallBack* callBack);
    void handleEvent();
    void setRevents(int revent);
    void enableReading();
    int getEvents();
    int getSockfd();
    /*增加缓冲区功能 */
    void setIndex(int index){index_ = index;}
    void enableWriting();
    void disableWriting();
    bool isWriting();
    int getIndex(){return index_;}
private:
    void update_();
    int sockfd_;
    int events_;
    int revents_;
    int index_;
    IChannelCallBack* callBack_;
    EventLoop* loop_;
};


#endif //MINI_MUDUO_CHANNEL_H
