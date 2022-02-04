#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <string>

std::string  msg1= "128\n";
char msg2[] = "Bye bye!\n";

class Sender{
private:
    std::string s_msg;

public:
    void send(std::string &message){

    s_msg = message;

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    sendto(sock, s_msg.c_str(), sizeof(msg1), 0,(struct sockaddr *)&addr, sizeof(addr));

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
  
    close(sock);
    }
};

int main()
{
    Sender message;

    message.send(msg1);

    return 0;
}