//
// Created by Jingjuan on 2020/8/10.
//

#ifndef MINI_MUDUO_EVENTLOOP_H
#define MINI_MUDUO_EVENTLOOP_H
#include "Channel.h"
#include "Epoll.h"

class Channel;
class Epoll;

class EventLoop {
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void update(Channel* channel);
private:
    bool quit_;
    Epoll* poller_;
};


#endif //MINI_MUDUO_EVENTLOOP_H
