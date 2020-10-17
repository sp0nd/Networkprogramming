// Networkprogram.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>         //printf
#include <stdlib.h>         //atoi
#include<string.h>          //strerror()
#include<errno.h>           //errno
#include<winsock2.h>
#include<WS2tcpip.h>        //inet_ntop

#pragma comment(lib,"ws2_32.lib")

#define MAXPENDING       5       // Maximum outstanding connection requests
#define STRINGBUFSIZE 1024       // BUFSIZE 할당

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    SOCKADDR_IN serverAddress, clientAddress;

    if (argc != 2)//Test for correct number of arguments
    {
        printf("sever <server Port>\n");
        return 0;
    }
    //소켓 라이브러리 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup() Error!\n");
        return 0;

    }

    int servPort = atoi(argv[1]); //First arg: local port
    //---------------------------------------------------------------------------------------
    //1.socket()- Create socket for incoming connections
    //---------------------------------------------------------------------------------------
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        printf("socket() failed![%d:%s]\n", errno, strerror(errno));
        return 0;
    }

    //Construct local address structure
    memset(&serverAddress, 0, sizeof(serverAddress)); //zero out structure
    serverAddress.sin_family = AF_INET;               //Ipv4 address family
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);//Any incoming interface
    serverAddress.sin_port = htons(servPort);         //Local port
    //---------------------------------------------------------------------------------------
    //2.bind() - bind to the local address
    //---------------------------------------------------------------------------------------
    if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        printf("bind() failed![%d:%s]\n", errno, strerror(errno));
        closesocket(serverSocket);
        return 0;
    }

    //---------------------------------------------------------------------------------------
    //3.listen() - mark the socket so it will listen for incoming connections
    //---------------------------------------------------------------------------------------
    if (listen(serverSocket, MAXPENDING) == SOCKET_ERROR)
    {
        printf("listen() failed![%d:%s]\n", errno, strerror(errno));
        closesocket(serverSocket);
        return 0;

    }
    char clientName[STRINGBUFSIZE];     // String to contain client address
    char recvBuffer[STRINGBUFSIZE];     // receive Buffer

    int clientAddressLen = sizeof(clientAddress);
    printf("Waiting to conntect...\n");
    for (;;)
    {
        clientName[0] = '\0'; //setempty
        recvBuffer[0] = '\0'; //setempty

        //---------------------------------------------------------------------------------------
        //4.accept() - Wait for a client to connect --> block mode
        //---------------------------------------------------------------------------------------
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        if (clientSocket < 0)
        {
            printf("accept() failed![%d:%s]\n", errno, strerror(errno));
            closesocket(clientSocket);
            continue;
        }
        printf("[%s:%d]", clientName, ntohs(clientAddress.sin_port));
        //---------------------------------------------------------------------------------------
        //5.recv() -Receive message from client
        //---------------------------------------------------------------------------------------
        int numBytesRcvd = recv(clientSocket, recvBuffer, STRINGBUFSIZE, 0);
        if (0 < numBytesRcvd)
        {
            if (STRINGBUFSIZE <= numBytesRcvd) recvBuffer[STRINGBUFSIZE - 1] = '\n';
            else                               recvBuffer[numBytesRcvd] = '\0';
            printf("recv:[%s]\n", recvBuffer);
        }
        else
            printf("recv:[]\n");

        closesocket(clientSocket); //close client socket
    }
    WSACleanup();

    return 1;
}

