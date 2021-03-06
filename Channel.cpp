//
// Created by Jingjuan on 2020/8/9.
//

#include "Channel.h"


Channel::Channel(EventLoop* loop, int sockfd)
    :sockfd_(sockfd)
    ,loop_(loop)
    ,events_(0)
    ,revents_(0)
    ,index_(-1)
    ,callBack_(nullptr){

}
void Channel::setCallBack(IChannelCallBack *callBack) {
    callBack_ = callBack;
}

void Channel::setRevents(int revents) {
    revents_ = revents;
}

void Channel::handleEvent() {
    if(revents_& EPOLLIN){
        callBack_->handleRead();
    }
    if(revents_& EPOLLOUT){
        callBack_->handleWrite();
    }
}

int Channel::getEvents() {
    return events_;
}

int Channel::getSockfd() {
    return  sockfd_;
}

void Channel::enableReading() {
    events_ |= EPOLLIN;
    update_();
}

void Channel::enableWriting() {
    events_ |= EPOLLOUT;
    update_();
}

void Channel::disableWriting() {
    events_ &= ~EPOLLOUT;
    update_();
}

bool Channel::isWriting() {
    return events_ & EPOLLOUT;
}



void Channel::update_() {
//    struct epoll_event ev;
//    ev.data.ptr = this;
//    ev.events = event_;
//    epoll_ctl(epollfd_,EPOLL_CTL_ADD,sockfd_,&ev);
    //所有的epoll相关的操作全在Epoll类中管理进行
    loop_->update(this);
}

/*增加缓冲区功能 */
