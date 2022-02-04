#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

//проверка условия
bool checkCondition(int &num)
{
    if ((num > 99) && (num % 32 == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//печатает реузльтат
void printRes(bool condition, int &num)
{
    if (condition)
    {
        std::cout << "Data received(" << num << ")\n"
                  << std::endl;
    }
    else
    {
        std::cout << "Error\n"
                  << std::endl;
    }
}

int main()
{
    int sock;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        std::cout << ("Problem with socket");
        return -1;
    }

    addr.sin_family = AF_INET;
    //порт к которому подключается
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cout << ("Problem with bind");
        return -1;
    }

    int num = 0;
    while (1)
    {
        bytes_read = recvfrom(sock, buf, 1024, 0, NULL, NULL);

        //преобразование в int
        num = std::stoi(std::string(buf, 0, bytes_read));
        //печатаем реузультат
        printRes(checkCondition(num), num);
    }

    return 0;
}