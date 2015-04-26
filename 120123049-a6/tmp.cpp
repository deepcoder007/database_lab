#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
	FILE* ptr = fopen("student_1.txt","r");
	char str[1000];

	int i;
	fclose(ptr);

	for(i=0;i<1000;i++)
	{
		ptr=fopen("student_1.txt","r");
		while( fgets(str,sizeof(str),ptr)!=NULL) ;
		fclose(ptr);
		cout<<i<<endl;
	}
	cout<<"DONE"<<endl;
	return 0;
}
