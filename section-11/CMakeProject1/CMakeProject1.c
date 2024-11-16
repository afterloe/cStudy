#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib ")  //linking to the library

int main()
{
	PHOSTENT hostinfo;
	printf("print id address \n");
	char hostname[255] = { 0 };
	if (NULL == hostname)
	{
		perror("hostname :");
		return EXIT_FAILURE;
	}
	gethostname(hostname, 255);
	printf("hostname is %s \n", hostname);

	if ((hostinfo = gethostbyname(hostname)) == NULL) //获得本地ipv4地址
	{
		perror("gethostname: ");
		errno = GetLastError();
		fprintf(stderr, "gethostbyname Error:%d \n", errno);
		return 1;
	}

	LPCSTR ip;

	while (*(hostinfo->h_addr_list) != NULL) //输出ipv4地址
	{
		ip = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);
		printf("ipv4 addr = %s\n\n", ip);
		hostinfo->h_addr_list++;
	}

	return EXIT_SUCCESS;
}