//#include <Windows.h>
//#include <stdio.h>
//#include <conio.h>
//#include <tchar.h>
//
//WSADATA wsaData;
//SOCKET sockO;
//SOCKET sockw;
//struct sockaddr_in addr;
//struct sockaddr_in client;
//#define PORT_NUM 9000
//
////IP �ּ� ���
//int getAddrHost(void)
//{
//	int i;
//	HOSTENT* lpHost;
//	IN_ADDR inaddr;
//	char szBuf[256], szIP[16];
//
//	// ����ó��
//	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
//	{
//		printf("WSAStartup Error\n");
//		return -1;
//	}
//	// ���� �ӽ��� ȣ��Ʈ �̸� ����
//	gethostname(szBuf, (int)sizeof(szBuf));
//
//	// ȣ��Ʈ ���� ���
//	lpHost = gethostbyname(szBuf);
//	// IP �ּ� ���
//	for (i = 0; lpHost->h_addr_list[i]; i++)
//	{
//		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
//	}
//	strcpy(szIP, inet_ntoa(inaddr));
//	printf("Build server : http://%s:%d\n", szIP, PORT_NUM);
//
//	WSACleanup();
//	return 0;
//}
//
//char* get_name(char* name) {
//
//}
//
//int main()
//{
//	int len;
//	int n;
//	int sockaddr_in_size = sizeof(struct sockaddr_in);
//	int recv_len = 0;
//	char buf[1024];
//	char path[1024];
//	char html[1024];
//
//	// IP ��巹�� ǥ��
//	if (getAddrHost() != 0)
//	{
//		printf("get IP address failed");
//		getch();
//		return -1;
//	}
//	//winsock2 �ʱ�ȭ
//	if (WSAStartup(MAKEWORD(2, 0), &wsaData))
//	{
//		puts("reset winsock failed");
//		getch();
//		return -1;
//	}
//	// ���� �����
//	sockO = socket(AF_INET, SOCK_STREAM, 0);
//	if (sockO == INVALID_SOCKET)
//	{
//		printf("socket : %d\n", WSAGetLastError());
//		getch();
//		return -1;
//	}
//
//	// ���ϼ���
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(PORT_NUM);
//	addr.sin_addr.S_un.S_addr = INADDR_ANY;
//
//	// ���� ���ε�
//	if (bind(sockO, (struct sockaddr*)&addr, sizeof(addr)) != 0)
//	{
//		printf("bind : %d\n", WSAGetLastError());
//		getch();
//		return -1;
//	}
//	// TCP Ŭ���̾�Ʈ�κ����� ���� �䱸�� ��ٸ��鼭 ���
//	if (listen(sockO, 5) != 0)
//	{
//		printf("listen : %d\n", WSAGetLastError());
//		getch();
//		return -1;
//	}
//
//	while (1)
//	{
//		len = sizeof(client);
//		sockw = accept(sockO, (struct sockaddr*)&client, &len);
//		if (sockw == INVALID_SOCKET)
//		{
//			printf("accept : %d\n", WSAGetLastError());
//			break;
//		}
//
//		// ���� �ʱ�ȭ
//		memset(path, 0, 1024);
//		memset(html, 0, 1024);
//
//		// ����
//		recv_len = recvfrom(sockw, buf, 1024, 0, (struct sockaddr*)&client, &sockaddr_in_size);
//		buf[recv_len - 1] = 0;
//		if (buf[0] == '\0')
//			strcpy(buf, NULL);
//
//		// ��� ǥ��
//		printf("%s \n", buf);
//
//		// method
//		for (int i = 0; i < strlen(buf); i++)
//		{
//			printf("%d\n", i);
//			if (buf[i] == 'G' && buf[i + 1] == 'E' && buf[i + 2] == 'T' && buf[i + 3] == ' ')
//			{
//				for (int j = 0; buf[i + 4 + j] != ' '; j++)
//				{
//					path[j] = buf[i + 4 + j];
//				}
//				break;
//			}
//			else if (buf[i] == 'P' && buf[i + 1] == 'O' && buf[i + 2] == 'S'  && buf[i +3] == 'T' &&buf[i +4] == ' ')
//			{
//				for (int j = 0; j < buf[i + 4 + j] != ' '; j++)
//				{
//					path[j] = buf[i + 4 + j];
//				}
//				break;
//			}
//		}
//		printf("request: %s \n", path);
//
//		// HTTP
//		char webpage[] =
//			"HTTP/1.1 200 OK\r\n"
//			"Server:Linux Web Server\r\n"
//			"Content-Type: text/html; charset=UTF-8\r\n\r\n"
//			"<!DOCTYPE html>\r\n"
//			"<html><head><title> My Web Page </title>\r\n"
//			"<style>body {background-color: #FFFF00 }</style></head>\r\n"
//			"<body><center><h1>Hello World!!</h1><br>\r\n"
//			"<img src=\"game.jpg\"></center></body></html>\r\n";
//
//		send(sockw, webpage, strlen(webpage), 0);
//
//		// ����� (�ϴ� ����)
//
//
//		// ����(HTML ����)
//		if (send(sockw, html , strlen(html), 0) < 1)
//		{
//			printf("send : %d\n", WSAGetLastError());
//			break;
//		}
//
//		// ���ϴݱ�
//		closesocket(sockw);
//	}
//	// winsock2 ����
//	closesocket(sockO);
//	WSACleanup();
//
//	return 0;
//}