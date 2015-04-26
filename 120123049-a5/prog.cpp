#include<stdio.h>
#include<stdlib.h>
#include<sys/file.h>
#include<fcntl.h>
#include<unistd.h>
#include<iostream>
#include<string.h>
using namespace std;

int main()
{
	char str[20];
	int fd = open("input.dat",O_RDWR, NULL );

/*
	struct flock flockstr;
	flockstr.l_type = F_WRLCK;
	flockstr.l_whence = SEEK_SET;
	flockstr.l_start = 0;
	flockstr.l_len = 88;
	fcntl(fd , F_SETLKW, &flockstr );
	*/
	int watch=0 ;

	if(fork())
	{
		struct flock flockstr;
		flockstr.l_type = F_RDLCK;
		flockstr.l_whence = SEEK_SET;
		flockstr.l_start = watch;
		flockstr.l_len = 88;
		fcntl(fd , F_SETLKW, &flockstr );

		int curr = watch; // to hold the current position , watch-> the start of the lock, 


		while( curr< (watch+88 ) )
		{
			lseek(fd, curr, SEEK_SET);
			read( fd, str, 11);
			// check if the current block is empty
			if(strcmp(str,"PID   BLNK\n")==0 ) // if the birth is empty
			{
				lseek(fd,curr, SEEK_SET);
				sprintf(str, "%5d  KZJ\n",getpid());
				write(fd, str, 11 );
				return 0;
			}
			curr+=11;
		}
		cout<<"No seat left for KZJ"<<endl;
		return 0;
	}
	watch+=88;

	if(fork())
	{
		struct flock flockstr;
		flockstr.l_type = F_RDLCK;
		flockstr.l_whence = SEEK_SET;
		flockstr.l_start = watch;
		flockstr.l_len = 88;
		fcntl(fd , F_SETLKW, &flockstr );

		int curr = watch; // to hold the current position , watch-> the start of the lock, 


		while( curr< (watch+88 ) )
		{
			lseek(fd, curr, SEEK_SET);
			read( fd, str, 11);
			// check if the current block is empty
			if(strcmp(str,"PID   BLNK\n")==0 ) // if the birth is empty
			{
				lseek(fd,curr, SEEK_SET);
				sprintf(str, "%5d  RDM\n",getpid());
				write(fd, str, 11 );
				return 0;
			}
			curr+=11;
		}
		cout<<"No seat left for RDM"<<endl;
		return 0;
	}
	watch+=88;

	if(fork())
	{
		struct flock flockstr;
		flockstr.l_type = F_RDLCK;
		flockstr.l_whence = SEEK_SET;
		flockstr.l_start = watch;
		flockstr.l_len = 88;
		fcntl(fd , F_SETLKW, &flockstr );

		int curr = watch; // to hold the current position , watch-> the start of the lock, 


		while( curr< (watch+88 ) )
		{
			lseek(fd, curr, SEEK_SET);
			read( fd, str, 11);
			// check if the current block is empty
			if(strcmp(str,"PID   BLNK\n")==0 ) // if the birth is empty
			{
				lseek(fd,curr, SEEK_SET);
				sprintf(str, "%5d  BPQ\n",getpid());
				write(fd, str, 11 );
				return 0;
			}
			curr+=11;
		}
		cout<<"No seat left for BPQ"<<endl;
		return 0;
	}
	watch+=88;

	if(fork())
	{
		struct flock flockstr;
		flockstr.l_type = F_RDLCK;
		flockstr.l_whence = SEEK_SET;
		flockstr.l_start = watch;
		flockstr.l_len = 88;
		fcntl(fd , F_SETLKW, &flockstr );

		int curr = watch; // to hold the current position , watch-> the start of the lock, 


		while( curr< (watch+88 ) )
		{
			lseek(fd, curr, SEEK_SET);
			read( fd, str, 11);
			// check if the current block is empty
			if(strcmp(str,"PID   BLNK\n")==0 ) // if the birth is empty
			{
				lseek(fd,curr, SEEK_SET);
				sprintf(str, "%5d  NGP\n",getpid());
				write(fd, str, 11 );
				return 0;
			}
			curr+=11;
		}
		cout<<"No seat left for NGP"<<endl;
		return 0;
	}
	watch+=88;

	if(fork())
	{
		struct flock flockstr;
		flockstr.l_type = F_RDLCK;
		flockstr.l_whence = SEEK_SET;
		flockstr.l_start = watch;
		flockstr.l_len = 88;
		fcntl(fd , F_SETLKW, &flockstr );

		int curr = watch; // to hold the current position , watch-> the start of the lock, 


		while( curr< (watch+88 ) )
		{
			lseek(fd, curr, SEEK_SET);
			read( fd, str, 11);
			// check if the current block is empty
			if(strcmp(str,"PID   BLNK\n")==0 ) // if the birth is empty
			{
				lseek(fd,curr, SEEK_SET);
				sprintf(str, "%5d  BPL\n",getpid());
				write(fd, str, 11 );
				return 0;
			}
			curr+=11;
		}
		cout<<"No seat left for BPL"<<endl;
		return 0;
	}
	watch+=88;

	if(fork())
	{
		struct flock flockstr;
		flockstr.l_type = F_RDLCK;
		flockstr.l_whence = SEEK_SET;
		flockstr.l_start = watch;
		flockstr.l_len = 88;
		fcntl(fd , F_SETLKW, &flockstr );

		int curr = watch; // to hold the current position , watch-> the start of the lock, 


		while( curr< (watch+88 ) )
		{
			lseek(fd, curr, SEEK_SET);
			read( fd, str, 11);
			// check if the current block is empty
			if(strcmp(str,"PID   BLNK\n")==0 ) // if the birth is empty
			{
				lseek(fd,curr, SEEK_SET);
				sprintf(str, "%5d  JHS\n",getpid());
				write(fd, str, 11 );
				return 0;
			}
			curr+=11;
		}
		cout<<"No seat left for JHS"<<endl;
		return 0;
	}
	watch+=88;

	if(fork())
	{
		struct flock flockstr;
		flockstr.l_type = F_RDLCK;
		flockstr.l_whence = SEEK_SET;
		flockstr.l_start = watch;
		flockstr.l_len = 88;
		fcntl(fd , F_SETLKW, &flockstr );

		int curr = watch; // to hold the current position , watch-> the start of the lock, 


		while( curr< (watch+88 ) )
		{
			lseek(fd, curr, SEEK_SET);
			read( fd, str, 11);
			// check if the current block is empty
			if(strcmp(str,"PID   BLNK\n")==0 ) // if the birth is empty
			{
				lseek(fd,curr, SEEK_SET);
				sprintf(str, "%5d  GWL\n",getpid());
				write(fd, str, 11 );
				return 0;
			}
			curr+=11;
		}
		cout<<"No seat left for GWL"<<endl;
		return 0;
	}
	watch+=88;

	if(fork())
	{
		struct flock flockstr;
		flockstr.l_type = F_RDLCK;
		flockstr.l_whence = SEEK_SET;
		flockstr.l_start = watch;
		flockstr.l_len = 88;
		fcntl(fd , F_SETLKW, &flockstr );

		int curr = watch; // to hold the current position , watch-> the start of the lock, 


		while( curr< (watch+88 ) )
		{
			lseek(fd, curr, SEEK_SET);
			read( fd, str, 11);
			// check if the current block is empty
			if(strcmp(str,"PID   BLNK\n")==0 ) // if the birth is empty
			{
				lseek(fd,curr, SEEK_SET);
				sprintf(str, "%5d  AGC\n",getpid());
				write(fd, str, 11 );
				return 0;
			}
			curr+=11;
		}
		cout<<"No seat left for AGC"<<endl;
		return 0;
	}
	watch+=88;

	if(fork())
	{
		struct flock flockstr;
		flockstr.l_type = F_RDLCK;
		flockstr.l_whence = SEEK_SET;
		flockstr.l_start = watch;
		flockstr.l_len = 88;
		fcntl(fd , F_SETLKW, &flockstr );

		int curr = watch; // to hold the current position , watch-> the start of the lock, 


		while( curr< (watch+88 ) )
		{
			lseek(fd, curr, SEEK_SET);
			read( fd, str, 11);
			// check if the current block is empty
			if(strcmp(str,"PID   BLNK\n")==0 ) // if the birth is empty
			{
				lseek(fd,curr, SEEK_SET);
				sprintf(str, "%5d NDLS\n",getpid());
				write(fd, str, 11 );
				return 0;
			}
			curr+=11;
		}
		cout<<"No seat left for NDLS"<<endl;
		return 0;
	}
	watch+=88;
}
