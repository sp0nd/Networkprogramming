#include <stdio.h>          // printf
#include <stdlib.h>         // atoi
#include <string.h>         // strerror()
#include <errno.h>          // errno
#include <winsock2.h>       // socket
#include <WS2tcpip.h>       // inet_ntop
#include <process.h>        // _beginthreadex/_endthreadex

#pragma comment(lib, "ws2_32.lib")

#define MAXPENDING         5  // Maximum outstanding connection requests
#define STRINGBUFSIZE   1024 

typedef struct _THREADPARAM
{
    char ip[16];
    int port;
    SOCKET sock;
}THREADPARAM, *LPTHREADPARAM;

// Thread Function
unsigned __stdcall ThreadFunc1(void* data)
{
    char recvBuffer[STRINGBUFSIZE] = "";    // receive Buffer
    LPTHREADPARAM param = (LPTHREADPARAM)data;

    printf("[%s:%d]connected!\n", param->ip, param->port);

    while (1)
    {
        //=========================================================================================
        // 5.recv() - Receive message from client
        //=========================================================================================
        int numBytesRcvd = recv(param->sock, recvBuffer, STRINGBUFSIZE, 0);
        if (0 < numBytesRcvd)
        {
            if (STRINGBUFSIZE <= numBytesRcvd)  recvBuffer[STRINGBUFSIZE - 1] = '\0';
            else                                recvBuffer[numBytesRcvd] = '\0';
            printf("[%s:%d]recv:[%s]\n", param->ip, param->port, recvBuffer);
        }
        else
            break;
    }
    closesocket(param->sock); // Close client socket

    printf("[%s:%d]disconnected!", param->ip, param->port);

    _endthreadex(0);
    return 0;
}

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    SOCKADDR_IN serverAddress, clientAddress;

    if (argc != 2) // Test for correct number of arguments
    {
        printf("std1Svr <Server Port>\n");
        return 0;
    }

    //소켓 라이브러리 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup() Error!\n");
        return 0;
    }

    int servPort = atoi(argv[1]); // First arg:  local port

    //=============================================================================================
    // 1.socket() - Create socket for incoming connections
    //=============================================================================================
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        printf("socket() failed![%d:%s]\n", errno, strerror(errno));
        return 0;
    }

    // Construct local address structure
    memset(&serverAddress, 0, sizeof(serverAddress));   // Zero out structure
    serverAddress.sin_family = AF_INET;                 // IPv4 address family
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);  // Any incoming interface
    serverAddress.sin_port = htons(servPort);           // Local port

    //=============================================================================================
    // 2.bind() - Bind to the local address
    //=============================================================================================
    if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        printf("bind() failed![%d:%s]\n", errno, strerror(errno));
        closesocket(serverSocket);
        return 0;
    }

    //=============================================================================================
    // 3.listen() - Mark the socket so it will listen for incoming connections
    //=============================================================================================
    if (listen(serverSocket, MAXPENDING) == SOCKET_ERROR)
    {
        printf("listen() failed![%d:%s]\n", errno, strerror(errno));
        closesocket(serverSocket);
        return 0;
    }

    char clientName[16];                 // String to contain client address
    int clientAddressLen = sizeof(clientAddress);

    printf("Waiting for connect...\n");

    for (;;)
    {
        clientName[0] = '\0'; // setempty

        //=========================================================================================
        // 4.accept() - Wait for a client to connect --> block mode
        //=========================================================================================
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        if (clientSocket < 0)
        {
            printf("accept() failed![%d:%s]\n", errno, strerror(errno));
            continue;
        }

        // clientSocket is connected to a client!
        if (inet_ntop(AF_INET, &clientAddress.sin_addr.s_addr, clientName, sizeof(clientName)) == NULL)
        {
            printf("Unable to get client address![%d:%s]\n", errno, strerror(errno));
            closesocket(clientSocket);
            continue;
        }

        LPTHREADPARAM param = (LPTHREADPARAM)malloc(sizeof(THREADPARAM));
        strncpy(param->ip, clientName, 16);
        param->port = ntohs(clientAddress.sin_port);
        param->sock = clientSocket;

        _beginthreadex(NULL, 0, &ThreadFunc1, (void*)param, 0, NULL);
    }
    WSACleanup();

    return 1;
}
