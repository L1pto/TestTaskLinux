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
#include <iostream>

using namespace std;

int main()
{

    //create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //Функция возвращает −1 в случае ошибки. Иначе, она возвращает целое число, представляющее присвоенный дескриптор.
    if (sock == -1)
    {
        return 1;
    }

    //create a hint structure for the server we're connectiong with
    //any ports
    int port = 54000;

    //localhost
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    //Type of protocol IPv4
    hint.sin_family = AF_INET;
    //The htons function converts a u_short from host to TCP/IP network byte order
    hint.sin_port = htons(port);

    //Функция пытается преобразовать строку, на которую указывает strptr, сохраняя двоичный результат с помощью указателя addrptr. При успешном выполнении ее возвращаемое значение равно 1.
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //Устанавливает соединение с сервером. Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr *)&hint, sizeof(hint));

    //Возвращает целое число, представляющее код ошибки: 0 означает успешное выполнение, а −1 свидетельствует об ошибке.
    if (connectRes == -1)
    {
        return 1;
    }

    char buf[4096];
    string userInput;

    do
    {

        //Enter linex of text
        cout << "> ";
        getline(cin, userInput);

        //Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);

        //TODO: Check ig that failed!
        if (sendRes == -1)
        {
            cout << "Could not send to server!\r\n";
            continue;
        }

        // Wait for response

        //fills the buf with 0
        memset(buf, 0, 4096);

        // чтение данных из сокета
        int bytesReceived = recv(sock, buf, 4096, 0);

        //TODO: Check ig that failed!
        if (bytesReceived == -1)
        {

            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //Display response
            cout << "SERVER" << string(buf, bytesReceived) << "\r\n";
        }

    } while (true);

    //  Close the socket
    close(sock);

    return 0;
}