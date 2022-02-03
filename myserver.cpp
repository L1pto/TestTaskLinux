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
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;

int main()
{

    //Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);

    //Функция возвращает −1 в случае ошибки. Иначе, она возвращает целое число, представляющее присвоенный дескриптор.
    if (listening == -1)
    {
        cout << "Can't create ac socket!";
        return -1;
    }

    sockaddr_in hint;

    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    //Для явного связывания сокета с некоторым адресом используется функция bind.
    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)
    {
        cout << "Can't bund to IP";
        return -2;
    }

    //Mark the socket for listening in
    if (listen(listening, SOMAXCONN) == -1)
    {
        cout << "Can't listen";
        return -3;
    }

    //Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    //Client's remote name
    char host[NI_MAXHOST]; 
    // Service (i.e. port) the client is connect on
    char svc[NI_MAXSERV];

    int clientSocket = accept( listening, (sockaddr *)&client, &clientSize);

    if(clientSocket == -1)
    {
    cout<<"Problem with client connecting";
    }

    //закрываем сокет
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0 , NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV,0);

    //если все работает мы получаем имя хоста 
    if(result){
        cout<< host<< " Connected on "<< svc <<endl;
    } else{
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout<< host<<" connected on "<< ntohs(client.sin_port) << endl;
    }

    //While receiving - display, echo message
    char buf[4096];

    while (true)
    {
        //clear the buffer
        memset(buf, 0, 4096);

        //Wait for a message
        int bytesRecv = recv(clientSocket,buf,4096,0);
        if(bytesRecv == -1){

            cout<<"There was a connection issue"<< endl;
        }

        if (bytesRecv == 0)
        {
            cout<<" The client disconeccted"<< endl;
            break;
        }

        //Display message
        cout<<" Received: "<< string(buf,0, bytesRecv) << endl;

        //Resend Message
        send(clientSocket, buf, bytesRecv + 1,0);

    }


    close(clientSocket);

    return 0;
}