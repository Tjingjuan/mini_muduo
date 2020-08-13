//
// Created by Jingjuan on 2020/8/11.
//

#include "Buffer.h"

const char * Buffer::peek() {
    return buf_.c_str();
}

void Buffer::append(const string &buf) {
    buf_.append(buf);
}

//可取的所有字符串长度
int Buffer::readableBytes() {
    return static_cast<int>(buf_.size());
}

void Buffer::retrieve(int len) {
    buf_ = buf_.substr(len,buf_.size());
}

//取出所有字符串
string Buffer::retrieveAllAsString() {
    return retrieveAsString(readableBytes());
}

// 取出长度为len的字符串
string Buffer::retrieveAsString(size_t len) {
    string result(peek(),len);
    retrieve(len);
    return result;
}