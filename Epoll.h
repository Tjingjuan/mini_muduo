//
// Created by Jingjuan on 2020/8/10.
//

#ifndef MINI_MUDUO_EPOLL_H
#define MINI_MUDUO_EPOLL_H
#include <sys/epoll.h>
#include "Channel.h"
#include <vector>
#include <iostream>
using namespace std;

#define MAX_EVENTS 500
class Channel;
class Epoll
{
public:
    Epoll();
    ~Epoll();
    void poll(vector<Channel*>* pChannels);
    void update(Channel* channel);
private:
    int epollfd_;
    struct epoll_event events_[MAX_EVENTS];
};


#endif //MINI_MUDUO_EPOLL_H
