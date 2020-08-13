//
// Created by Jingjuan on 2020/8/11.
//

#ifndef MINI_MUDUO_BUFFER_H
#define MINI_MUDUO_BUFFER_H

#include <string>
using namespace std;

class Buffer
{
public:
    Buffer(){}
    ~Buffer(){}
    const char* peek();
    int readableBytes();
    void retrieve(int len);
    void append(const string& buf);
    string retrieveAllAsString();
    string retrieveAsString(size_t len);
private:
    string buf_;
};

#endif //MINI_MUDUO_BUFFER_H
