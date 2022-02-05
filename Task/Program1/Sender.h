#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Sender
{
private:
    std::string s_msg;

public:
    void send(std::string &message);
};