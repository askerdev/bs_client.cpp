#pragma comment(lib, "ws2_32.lib")
#include "Application.h"
#include <iostream>
#include <winsock2.h>

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	Application app;
	app.Main();

	WSACleanup();
	return 0;
}