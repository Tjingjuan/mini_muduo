//
// Created by Jingjuan on 2020/8/14.
//

#ifndef MINI_MUDUO_ICHANNELCALLBACK_H
#define MINI_MUDUO_ICHANNELCALLBACK_H

class IChannelCallBack{
public:
//    void virtual OnIn(int sockfd)=0;
    void virtual handleWrite() = 0;
    void virtual handleRead() = 0;
};


#endif //MINI_MUDUO_ICHANNELCALLBACK_H
