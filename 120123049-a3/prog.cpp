#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/errno.h>
#include<signal.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string>
#include<cstring>
#include<string>
using namespace std;


// read input from 0
int main()
{
	mkfifo("fifo_1", 0666 );     // used as a residual buffer
	mkfifo("fifo_2", 0666 );     // used as synonym of original data buffer
	mkfifo("out_fifo", 0666 );
	mkfifo("counting_fifo",0666);    // stores the count of the number of records
	char c[2];
	char buf[10];

	int count=0 ;      // stores the count of the records
	int curr=0;       // stores the current value to be stored

	// read the records from the fifo and count the number of records

	switch(fork())
	{
	case 0:   // the child process : TODO: open the 0 fd to count the records and write it to fifo_1
		{
			int fd1w=open("fifo_1", O_WRONLY  );
			int fifo_count=open("counting_fifo", O_WRONLY  );
			while( read( 0, c , 1 )!=0 )
			{
				if( c[0]=='\n' )
				{
					count++;
				}
				write(fd1w,c,1);
			}
			cout<<"No. of records = "<<count<<endl;
			// The whole data is in fifo_1 now
			sprintf(buf,"%d",count);
			write( fifo_count , buf , strlen(buf) +1 );
			close(fd1w);
			close(fifo_count);
			return 0;
			break;
		}
	default:
		{
			int fd1d=open("fifo_1", O_RDONLY );   // fifo1 is having all the data
			int fifo_count_r = open("counting_fifo", O_RDONLY );
			read(fifo_count_r, buf, sizeof(buf) );
			count = atoi(buf);

			// Start a child process that will take data from 'fifo_1' and pass it to 'fifo_2'
			// the parent process will read data from 'fifo_2' and process the data and pass it to 'fifo_1'
			switch(fork())
			{
			case 0:   // The child process
				{
					int fd2w = open("fifo_2", O_WRONLY );
					char buf2[5];
					while( read(fd1d, buf2, 1 ) !=0 ) 
						write( fd2w , buf2, 1 ) ;
					return 0;
					break;
				}
			default :  // The parent process
				{
					int fd2d = open("fifo_2", O_RDONLY ) ;
					int fd1w = open("fifo_1", O_WRONLY ) ;
					int out_fifo  = open("out_fifo", O_WRONLY );   // for writing the output
					count--;          // index of the last record
					while( count>=0 )   // while there is record in the pipe
					{
						curr=0;   // index of the current record that is going to be processed , starting from 0
						while( read( fd2d, c , 1 )!=0 )
						{
							if( c[0]=='\n' )
							{ curr++; }
							write(fd1w,c,1);
							if( curr==count )   // i.e. the last process to be processed
							{	
								break;
							}
						}
						   // the final record to be processed
						read(fd2d , c, 1);
						while( c[0]!='\n' )
						{
							write( out_fifo, c, 1);
							read( fd2d, c, 1);
						}
						write( out_fifo, c, 1);
						count--;
					}
				}
			}
		}
	}

	return 0;
}
	
	
