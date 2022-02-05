#include "Sender.h"

void Sender::send(std::string &message)
{
    s_msg = message;

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    sendto(sock, s_msg.c_str(), sizeof(s_msg), 0, (struct sockaddr *)&addr, sizeof(addr));

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    close(sock);
}