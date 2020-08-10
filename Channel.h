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
    void virtual OnIn(int sockfd){};
};


//class Channel {
//public:
//    Channel(int epollfd,int sockfd);
//    ~Channel();
//    void setCallBack(IChannelCallBack* callBack);
//    void handleEvent();
//    void setRevent(int revent);
//    int getSockfd();
//    void enableReading();
//
//private:
//    void updata_();
//    int epollfd_;
//    int sockfd_;
//    int event_;
//    int revent_;
//    IChannelCallBack* callBack_;
//};
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
private:
    void update_();
    int sockfd_;
    int events_;
    int revents_;
    IChannelCallBack* callBack_;
    EventLoop* loop_;
};


#endif //MINI_MUDUO_CHANNEL_H
