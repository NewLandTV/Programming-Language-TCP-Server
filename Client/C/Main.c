#include <stdio.h>
#include <WinSock2.h>

#define BUFFER_SIZE 2048

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int main(void)
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 1;
	}

	SOCKET clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket == INVALID_SOCKET)
	{
		return 1;
	}

	SOCKADDR_IN serverAddrIn;

	serverAddrIn.sin_family = AF_INET;
	serverAddrIn.sin_port = htons(2222);
	serverAddrIn.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (connect(clientSocket, (SOCKADDR*)&serverAddrIn, sizeof(SOCKADDR_IN)))
	{
		return 1;
	}

	char buffer[BUFFER_SIZE];

	memset(buffer, 0, BUFFER_SIZE);
	scanf("%s", buffer);

	buffer[strlen(buffer) + 1] = 0;

	send(clientSocket, buffer, strlen(buffer), 0);
	recv(clientSocket, buffer, BUFFER_SIZE, 0);

	buffer[strlen(buffer) + 1] = 0;

	printf("From server : %s\n", buffer);
	closesocket(clientSocket);
	WSACleanup();

	return 0;
}