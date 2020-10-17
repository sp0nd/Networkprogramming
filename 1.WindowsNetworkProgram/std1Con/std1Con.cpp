// std1Console.cpp
//

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	int ret;
	//-----------------------------------------------------------------------
	// validate

	if (argc != 4)
	{
		printf("usage:std1Con <serverip> <port> <message)\n");
		return 1;
	}
	char* serverip = argv[1];
	short port = (short)atoi(argv[2]);
	char* msg = argv[3];

	//-----------------------------------------------------------------------
	// initialize windows socket
	WSADATA wsaData = { 0 };
	ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		printf("WSAStartup failed: %d\n", ret);
		return 1;
	}

	//-----------------------------------------------------------------------
	// socket
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		printf("socket() failed![%d]\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	//-----------------------------------------------------------------------

	sockaddr_in name;
	memset(&name, 0x00, sizeof(name));
	name.sin_family = AF_INET;
	inet_pton(AF_INET, serverip, &name.sin_addr);
	name.sin_port = htons(port);

	// connect
	if (connect(sock, (sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
	{
		printf("socket() failed![%d]\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	}


	// send
	if (send(sock, msg, strlen(msg), 0) == SOCKET_ERROR)
	{
		printf("send() failed![% d]\n", WSAGetLastError());
	}
	else
		printf("success\n");

	closesocket(sock);
	WSACleanup();
}
