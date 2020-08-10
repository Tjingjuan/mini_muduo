#include "TcpServer.h"

int main(){
    EventLoop loop;
    TcpServer tcpserver(&loop);
    tcpserver.start();
    loop.loop();
    return 0;
}