#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<dirent.h>
#include<unistd.h>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<set>
#include<sys/stat.h>
#include<signal.h>
using namespace std;



//vector<string> dept_folder_list;   // a list of all the dept-> used to traverse the folder
//map<string,string>  course_list;    // a mapping from the course code to the course name
//map<string,vector<string> >  course_student_list;        // a mapping from the course to the vector of students who are attending that course
//map<string,vector<string> >  student_course_list;     // a mapping from the student roll_no to the list of courses he is takign
//map<string,string>  student_roll_name;      // a mapping of the student roll_no to the student names

//map<string,FILE* > dept_name_file;

char buffer[100];
char buffer2[10000000];
char buffer3[10000000];
string b_buf1,b_buf2,b_buf3;
char* buf1;
char* buf2;
char* buf3;
char* save1;
char* save2;
char* save3;



int main()
{
	// Initialize the pipes
	char base[]="./database/";
	string b_base=base;
	DIR* dir = opendir(base);
	DIR* dir2;
	FILE* ptr;
	struct dirent* files;
	struct dirent* files2;
	struct stat statbuf;
	int file1_pipe[2];
	int file2_pipe[2];
	pipe( file1_pipe );   
	pipe( file2_pipe );

	string course1,course2;  // the code of the courses
	string course1_name, course2_name;  // the name of the course
	cout<<"Enter the name of the two courses : "<<endl;
	cin>>course1;
	cin>>course2;
	while((files=readdir(dir))!=NULL )
	{
		if( strcmp(files->d_name,"index.txt")==0)    // for reading the course list
		{
			ptr=fopen( (base+string(files->d_name)).c_str(),"r");
			while(fgets(buffer,sizeof(buffer),ptr)!=NULL)
			{
				b_buf1=strtok(buffer,",");
				b_buf2=strtok(NULL,"\n");
				if( !b_buf1.compare(course1) )
				{
					course1_name=b_buf2;
				}
				if( !b_buf1.compare(course2) )
				{
					course2_name=b_buf2;
				}
			}
			fclose(ptr);
		}
	}
	closedir(dir);
	dir = opendir(base);

	while((files=readdir(dir))!=NULL)
	{
		if( strcmp(files->d_name,".")==0 || strcmp(files->d_name,"..")==0 )
			continue;

		stat( (b_base + string(files->d_name)).c_str() , &statbuf );
		if(S_ISDIR(statbuf.st_mode))   // If it is a department directory
		{
			dir2=opendir( (b_base+string(files->d_name) ).c_str() );

			// Reading files inside dir
			while( (files2=readdir(dir2))!=NULL)  // here files2 will be the courses
			{
				if( strcmp(files2->d_name,".")==0 || strcmp(files2->d_name,"..")== 0)
					continue;
				cout<<"COURSE: "<<files2->d_name<<endl;


				if( strcmp( files2->d_name , ( course1 + string(".txt") ).c_str() ) == 0 )  // The course 1 file is found
				{
					cout<<"COURSE 1 IDENTIFIED"<<endl;
					ptr = fopen( (b_base + string(files->d_name) + string("/") + string(files2->d_name) ).c_str() ,"r");
					while( fgets(buffer,sizeof(buffer),ptr)!=NULL)
					{
					// file1_pipe -> 0 for read and 1 for write
						write(file1_pipe[1], buffer, strlen(buffer));
					}
					fclose(ptr);
					close(file1_pipe[1]);
					break;
				}


				if( strcmp( files2->d_name , ( course2 + string(".txt") ).c_str() ) == 0 )  // The course 2 file is found
				{
					cout<<"COURSE 2 IDENTIFIED"<<endl;
					ptr = fopen( (b_base + string(files->d_name) + string("/") + string(files2->d_name) ).c_str() ,"r");
					while( fgets(buffer,sizeof(buffer),ptr)!=NULL)
					{
					// file2_pipe -> 0 for read and 1 for write
						write(file2_pipe[1], buffer, strlen(buffer));
					}
					fclose(ptr);
					close(file2_pipe[1]);
					break;
				}
			}

		}
	}

	 read(file1_pipe[0],buffer2,sizeof(buffer2));
	 read(file2_pipe[0],buffer3,sizeof(buffer2));
	close(file1_pipe[0]);
	close(file2_pipe[0]);
	close(file1_pipe[1]);
	close(file2_pipe[1]);



	// FINAL PROCESSING
	
	buf1=strtok_r(buffer2,"\n",&save1);
	buf2=strtok_r(buffer3,"\n",&save2);
	long int num1,num2;

bool btech,mtech,phd;
btech=mtech=phd=false;  // true represents the current variable

btech=true;
cout<<"PRINTING B.TECH STUDENTS: "<<endl;
	while(1)
	{
		num1=atoi(strtok(buf1,","));  // the roll of current line
		b_buf1=strtok(NULL,",");     // the name of the current stuent

		num2=atoi(strtok(buf2,","));
		b_buf2=strtok(NULL,",");

		if( num1 == num2 )
		{
			if( mtech==false && string(strtok(buf1,",")).substr(2,2).compare(string("41"))==0 )
			{
				cout<<endl<<"PRINTING M.TECH STUDENTS"<<endl<<endl;
				mtech=true;
				btech=false;
			}
			if( phd==false && string(strtok(buf1,",")).substr(2,2).compare(string("61"))==0 )
			{
				cout<<endl<<"PRINTING Ph.D. STUDENTS"<<endl<<endl;
				mtech=false;
				phd=true;
			}
			buf1=strtok_r(NULL,"\n",&save1);
			buf2=strtok_r(NULL,"\n",&save2);
			cout<<num1<<"  :  "<<b_buf1<<endl;
		}
		else if( num1 < num2 )
		{
			buf1=strtok_r(NULL,"\n",&save1);
		}
		else
		{
			buf2=strtok_r(NULL,"\n",&save2);
		}

	}
	return 0;

}


