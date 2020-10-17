// networkprograming.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//lib error =link
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

int main(int argc,char* argv[])
{
    int ret;
    //----------------------------------------------------------------------------
    //validate
    if (argc != 4)
    {
        printf("usage:NetworkCon <IP> <port> <message>\n");
        return 1;
    }
    char* ip = argv[1];
    short port = (short)atoi(argv[2]);
    char* msg = argv[3];
    //----------------------------------------------------------------------------
    // initialize windows socket
    WSADATA wsaData = { 0 };
    ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        printf("WSAStartup failed: %d\n", ret);
        return 1;
    }
    //----------------------------------------------------------------------------
    //socket
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        printf("socket() failed![%d]\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //----------------------------------------------------------------------------
    sockaddr_in name;
    memset(&name, 0x00, sizeof(name));
    name.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &name.sin_addr);
    name.sin_port = htons(port);
    //connect
    if (connect(sock, (sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
    {
        printf("socket() failed[%d]\n", WSAGetLastError());
        closesocket(sock);
        return 1;
    }
    //----------------------------------------------------------------------------
    //send
    if (send(sock, msg, strlen(msg), 0) == SOCKET_ERROR)
    {
        printf("send() failed![%d]\n", WSAGetLastError());
    }
    else
        printf("success");

    closesocket(sock);
    WSACleanup();
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
