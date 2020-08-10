//
// Created by Jingjuan on 2020/8/10.
//
#include "EventLoop.h"

EventLoop::EventLoop()
        :quit_(false)
        ,poller_(new Epoll()) // Memory Leak !!!
{
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
    }
}

void EventLoop::update(Channel* channel)
{
    poller_->update(channel);
}