//
// Created by Jingjuan on 2020/8/10.
//
#include "EventLoop.h"
#include <sys/eventfd.h>
#include <unistd.h>

EventLoop::EventLoop()
        :quit_(false)
        ,poller_(new Epoll()) // Memory Leak !!!
{
    eventfd_ = createEventfd();
    wakeupChannel_ = new Channel(this,eventfd_); //Memory Leak !!!
    wakeupChannel_->setCallBack(this);
    wakeupChannel_->enableReading();
}

EventLoop::~EventLoop()
{}

void EventLoop::loop()
{
    while(!quit_)
    {
        vector<Channel*> channels;
        poller_->poll(&channels);  //epoll_wait

        vector<Channel*>::iterator it;
        for(it = channels.begin(); it != channels.end(); ++it)
        {
            (*it)->handleEvent();
        }
        doPendingFunctors();
    }
}

void EventLoop::update(Channel* channel)
{
    poller_->update(channel);
}

void EventLoop::queueLoop(IRun *pRun) {
    pendingFunctors_.push_back(pRun);
    wakeup();
}

void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = ::write(eventfd_, &one, sizeof one);
    if (n != sizeof one)
    {
        cout << "EventLoop::wakeup() writes " << n << " bytes instead of 8" << endl;
    }
}

int EventLoop::createEventfd() {
    int eventfd = ::eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
    if(eventfd < 0){
        cout<<"Failed in event"<<endl;
    }
    return eventfd;
}

void EventLoop::handleRead() {
    uint64_t one = 1;
    ssize_t n = ::read(eventfd_, &one, sizeof one);
    if (n != sizeof one) {
        cout << "EventEventLoop::handleRead() reads " << n << " bytes instead of 8" << endl;
    }
}
void EventLoop::handleWrite() {

}

void EventLoop::doPendingFunctors() {
    vector<IRun*> tempRuns;
    tempRuns.swap(pendingFunctors_);
    vector<IRun*>::iterator it;
    for(it = tempRuns.begin(); it != tempRuns.end(); ++it)
    {
        (*it)->run();
    }
}