//
// Created by Jingjuan on 2020/8/10.
//

#include "Epoll.h"


Epoll::Epoll()
{
    epollfd_ = ::epoll_create(1);
    if (epollfd_ <= 0)
        cout << "epoll_create error, errno:" << epollfd_ << endl;
}

Epoll::~Epoll()
{}

void Epoll::poll(vector<Channel*>* pChannels)
{
    int fds = ::epoll_wait(epollfd_, events_, MAX_EVENTS, -1);
    if(fds == -1)
    {
        cout << "epoll_wait error, errno:" << errno << endl;
        return;
    }
    for(int i = 0; i < fds; i++)
    {
        Channel* pChannel = static_cast<Channel*>(events_[i].data.ptr);
        pChannel->setRevents(events_[i].events);
        pChannels->push_back(pChannel);
    }
}

void Epoll::update(Channel* channel)
{
    struct epoll_event ev;
    ev.data.ptr = channel;
    ev.events = channel->getEvents();
    int fd = channel->getSockfd();
    ::epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev);
}