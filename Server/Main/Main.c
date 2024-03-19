#include <stdio.h>
#include <WinSock2.h>

#define BUFFER_SIZE 2048

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 1;
	}

	SOCKET listeningSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (listeningSocket == INVALID_SOCKET)
	{
		return 1;
	}

	SOCKADDR_IN serverAddrIn;

	serverAddrIn.sin_family = AF_INET;
	serverAddrIn.sin_port = htons(2222);
	serverAddrIn.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(listeningSocket, (SOCKADDR*)&serverAddrIn, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		return 1;
	}

	if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		return 1;
	}

	char buffer[BUFFER_SIZE];

	memset(buffer, 0, BUFFER_SIZE);

	SOCKET clientSocket;
	SOCKADDR_IN clientAddrIn;
	int clientAddrInLength = sizeof(SOCKADDR_IN);

	clientSocket = accept(listeningSocket, (SOCKADDR*)&clientAddrIn, &clientAddrInLength);

	recv(clientSocket, buffer, BUFFER_SIZE, 0);

	buffer[strlen(buffer) + 1] = 0;

	printf("Recv Data : %s", buffer);
	send(clientSocket, buffer, strlen(buffer), 0);
	closesocket(clientSocket);
	closesocket(listeningSocket);
	WSACleanup();

	return 0;
}