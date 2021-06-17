#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#define BUF_SIZE 1024
#define SMALL_BUF 100

char webpage[] =
"HTTP/1.1 200 OK\r\n"
"Server:Linux Web Server\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html><head><title> My Web Page </title>\r\n"
"<style>body {background-color: #0101DF }</style></head>\r\n"
"<body><center><h1>Hello World!!</h1><br>\r\n"
"<img src=\"dog.jpg\"></center></body></html>\r\n";

void error_handling(char* message);

int main(int argc, char* argv[])
{
	struct sockaddr_in serv_adr, clnt_adr;
	int serv_sock, clnt_sock;
	int sin_len;
	char buf[BUF_SIZE];
	int fdimg;
	char img_buf[500000];

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	//fdimg = fopen("dog.txt", "rb");

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));
	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock, 20) == -1)
		error_handling("listen() error");

	while (1)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &sin_len);
		printf("Connection....");
		read(clnt_sock, buf, 2047);
		printf("%s\n", buf);
		if (!strncmp(buf, "GET /dog.jpg", 12)) {
			fdimg = open("dog.jpg", O_RDONLY);
			read(fdimg, img_buf, sizeof(img_buf));
			write(clnt_sock, img_buf, sizeof(img_buf));

			close(fdimg);
		}
		else
			write(clnt_sock, webpage, sizeof(webpage) - 1);
		puts("closing....");

	}
	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
