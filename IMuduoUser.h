//
// Created by Jingjuan on 2020/8/10.
//

#ifndef MINI_MUDUO_IMUDUOUSER_H
#define MINI_MUDUO_IMUDUOUSER_H

#include <string>
//#include "TcpConnection.h"
using namespace std;

class TcpConnection;

class IMuduoUser{
public:
    void virtual onConnection(TcpConnection* pCon) = 0;
    void virtual onMessage(TcpConnection* pCon, string* data) = 0;
};

#endif //MINI_MUDUO_IMUDUOUSER_H
