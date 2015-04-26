// This program is for sorting student_2.txt
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;

struct record
{
	int sid;
	string sname;
	float rating;
	float age;
};

record buf1[50]; record buf2[50]; record buf[100];

int i; char str[1000]; char str_a[1000] ; char str_b[1000]; char str_aa[1000]; char str_bb[1000]; char* tok_1; char* tok_2;

int main()
{
	FILE* ptr = fopen("student_2.txt","r");
	FILE* fl = fopen("buf.txt","w");
	FILE* fl2;
	FILE* fl_a;
	FILE* fl_b;
	int off_1,off_2;
	// read this file and split it into volumes of 1  record
	while( fgets(str,sizeof(str),ptr) != NULL )
	{
		fputs(str,fl );
		fprintf(fl,"$\n");
	}
	fclose(ptr);
	fclose(fl);

//	return 0;

	// now start merging of record
	while(1)
	{
		int len;
		cout<<"ITER START"<<endl;
		fl_a = fopen("buf.txt","r");
		fl_b = fopen("buf.txt","r");
		fl2 = fopen("buf2.txt","w");
		off_1=off_2 =0;   // the offset of the respective files
		fseek(fl_a, 0, SEEK_END);
		len=ftell(fl_a);
		fseek(fl_a, 0, SEEK_SET);
		fseek(fl_b, 0, SEEK_SET);
		
		bool change=false; // to denote if a change was made 

		// Now start the processing part
		while(1)
		{
			change=false;
			// find the record break for fl_b
			fseek(fl_a, off_1,SEEK_SET);
			fseek(fl_b, off_2,SEEK_SET);
			if( (len-ftell(fl_a))<5) break;  // if the end of the file
			do
			{
				fgets(str, sizeof(str), fl_b);
			}while( strcmp(str,"$\n")!=0 );
			change=true;
			off_2 = ftell(fl_b );

			// now start the merge of these 2 sections
			// Initialize the first section
			fgets(str_a, sizeof(str_a), fl_a );
			fgets(str_b, sizeof(str_b), fl_b );
			while(1)
			{
				if( strcmp(str_a,"$\n")== 0 || strcmp(str_b,"$\n")== 0 ) break;   // end of string reached
				strcpy(str_aa,str_a);
				strcpy(str_bb,str_b);
				tok_1=strtok(str_aa,",");
				tok_2=strtok(str_bb,",");
				if( atoi(tok_1) <= atoi(tok_2) )
				{
					fputs(str_a,fl2);
					fgets(str_a, sizeof(str_a),fl_a );
				}
				else
				{
					fputs(str_b,fl2);
					fgets(str_b, sizeof(str_b),fl_b );
				}
			}
			if( strcmp(str_a,"$\n")==0 ) // if first buffer was exhausted
			{
				do
				{
					fputs(str_b,fl2);
					fgets(str_b, sizeof(str_b),fl_b);
				}while( strcmp( str_b, "$\n")!= 0 );
			}
			else if( strcmp( str_b, "$\n") == 0 )
			{
				do
				{
					fputs(str_a,fl2);
					fgets(str_a, sizeof(str_a), fl_a);
				}while( strcmp( str_a, "$\n")!=0 );
			}
			fprintf(fl2,"$\n");
			off_2=off_1=ftell(fl_b);
		}

		fclose(fl_a);
		fclose(fl_b);
		fclose(fl2);
		rename("buf2.txt","buf.txt");
	}
	return 0;
}

