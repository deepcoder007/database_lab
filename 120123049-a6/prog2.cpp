#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fcntl.h>
#include<unistd.h>
#include<string>
#include<cstring>
using namespace std;


char str1[1000];
char str2[1000];
char str_tmp[1000];
char* tok1,*tok1a,*tok1b,*tok1c;
char* tok2,*tok2a,*tok2b,*tok2c;

int main()
{
	FILE* out = fopen("diff.txt","w");
	FILE* f1 = fopen("student_1.txt","r");
	FILE* f2 = fopen("buf.txt","r");  

	fgets(str2,sizeof(str2), f2);
	while(1)
	{
		if( fgets(str1, sizeof(str1), f1 ) == NULL ) break; 
		tok1 = strtok(str1," ");
		tok1a = strtok(NULL," ");
		tok1b = strtok(NULL," ");
		tok1c = strtok(NULL," \n");

		// fast track the f2
		strcpy(str_tmp, str2);
		while( atoi( strtok(str_tmp,",") ) < atoi(tok1) )
		{
			if( fgets(str2,sizeof(str2),f2) == NULL ) goto outskip; // jump to the outermost loop on the end of file 2
			strcpy(str_tmp, str2);
		}
		strcpy(str_tmp, str2);
		if( atoi( strtok(str_tmp,",") ) > atoi (tok1 ) )
		{
			fprintf(out,"%s\n",tok1);
		}

	}
	outskip:
	while( fgets(str1,sizeof(str1), f1) != NULL )
	{
		tok1 = strtok(str1," ");
		tok1a = strtok(NULL," ");
		tok1b = strtok(NULL," ");
		tok1c = strtok(NULL," \n");
		fprintf(out,"%s\n",tok1);
	}
	fclose(out);
	fclose(f1);
	fclose(f2);
	return 0;

}
