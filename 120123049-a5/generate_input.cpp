#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
using namespace std;


int main()
{
	FILE* ptr;
	int i,j;

	ptr=fopen("input.dat","w");
	for(i=0;i<72;i++)
	{
		fprintf(ptr,"PID   BLNK\n");
	}
	fclose(ptr);
	return 0;
}

	
