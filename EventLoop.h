//
// Created by Jingjuan on 2020/8/10.
//

#ifndef MINI_MUDUO_EVENTLOOP_H
#define MINI_MUDUO_EVENTLOOP_H
#include "Channel.h"
#include "Epoll.h"
#include "IRun.h"
#include <vector>
#include "IChannelCallBack.h"
using namespace std;

class Channel;
class Epoll;

class EventLoop:public IChannelCallBack{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void update(Channel* channel);
    // add buffer
    void queueLoop(IRun* pRun);
    void virtual handleRead();
    void virtual handleWrite();

private:
    bool quit_;
    Epoll* poller_;
    // add buffer
    void wakeup();
    int createEventfd();
    void doPendingFunctors();
    int eventfd_;
    Channel* wakeupChannel_;
    vector<IRun* > pendingFunctors_;
};


#endif //MINI_MUDUO_EVENTLOOP_H
