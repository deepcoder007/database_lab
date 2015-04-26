#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fcntl.h>
#include<sys/errno.h>
#include<signal.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string>
#include<cstring>
using namespace std;


int main()
{
	mkfifo("myfifo", 0666 );
	int fd=open("myfifo", O_WRONLY );
	char str[100];
	strcpy(str,"Thank you");
	write(fd,str,sizeof(str)) ;
	close(fd);
	return 0;
}
	
	
