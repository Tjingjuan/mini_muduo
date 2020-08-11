//
// Created by Jingjuan on 2020/8/10.
//

#include "Epoll.h"

const int kNew = -1;
const int kAdded = 1;

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

void Epoll::update(Channel* pChannel)
{
    struct epoll_event ev;
    ev.data.ptr = pChannel;
    ev.events = pChannel->getEvents();
    int fd = pChannel->getSockfd();

    int index = pChannel->getIndex();
    if(index == kNew){
        pChannel->setIndex(kAdded);
        ::epoll_ctl(epollfd_, EPOLL_CTL_ADD,fd, &ev);
    }else{
        ::epoll_ctl(epollfd_,EPOLL_CTL_MOD,fd,&ev);
    }
}