#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fcntl.h>
#include<sys/errno.h>
#include<signal.h>
#include<sys/stat.h>
#include<unistd.h>
#include<cstring>
#include<string>
using namespace std;


int main()
{
//	mkfifo("myfifo", 0666 );
	int fd=open("out_fifo", O_RDONLY );
	//char str[100];;
	char c;
	char str[100];
	while( read( fd, str,1 ) !=0 )
		cout<<str[0];
	close(fd);
	return 0;
}
	
	
