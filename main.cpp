#include "EchoServer.h"

int main(){
    EventLoop loop;
//    TcpServer tcpserver(&loop);
//    tcpserver.start();
    EchoServer echoServer(&loop);
    echoServer.start();
    loop.loop();
    return 0;
}