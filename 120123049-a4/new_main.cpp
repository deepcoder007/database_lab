#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<dirent.h>
#include<cstring>
#include<set>
#include<vector>
#include<string>
#include<map>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/mman.h>
using namespace std;



vector<string> dept_folder_list;   // a list of all the dept-> used to traverse the folder
map<string,string>  course_list;    // a mapping from the course code to the course name
map<string,vector<string> >  course_student_list;        // a mapping from the course to the vector of students who are attending that course
map<string,vector<string> >  student_course_list;     // a mapping from the student roll_no to the list of courses he is takign
map<string,string>  student_roll_name;      // a mapping of the student roll_no to the student names

map<string,FILE* > dept_name_file;

char buffer[1000];
char buffer2[1000];
char* buf2;
char* buf3;
string b_buf1,b_buf2,b_buf3;


int main()
{
	char base[]="./database/";
	string b_base=base;

	DIR* dir = opendir(base);
	FILE* ptr;
	struct dirent* files;
	while((files=readdir(dir))!=NULL)
	{
		if( strcmp(files->d_name,"index.txt")==0)    // for reading the course list
		{
			ptr=fopen( (base+string(files->d_name)).c_str(),"r");
			while(fgets(buffer,sizeof(buffer),ptr)!=NULL)
			{
				b_buf1=strtok(buffer,",");
				b_buf2=strtok(NULL,"\n");
				course_list[b_buf1]=b_buf2;
			}
			fclose(ptr);
		}
		if( strcmp(files->d_name,"..")!=0 && strcmp(files->d_name,"index.txt")!=0 && strcmp(files->d_name,".")!=0 )	
		{
			dept_folder_list.push_back(string(files->d_name));
		}
	}

	string curr_course;
	string course_code;

	// Now start reading all the departments
	vector<string>::iterator it;
	for(it = dept_folder_list.begin() ; it!= dept_folder_list.end() ; it++ )
	{
		dir = opendir( (b_base + (*it)).c_str() );   // open the directory of the current directory
		while(( files=readdir(dir))!=NULL)    // for all the files in the dept.
		{
			if( strcmp(files->d_name,"..")!=0 && strcmp(files->d_name,".") )
			{
				// Process each course ..... 

				curr_course = b_base + (*it) +string("/")+ string(files->d_name);
				course_code = string(files->d_name).substr(0,5);

				ptr = fopen(curr_course.c_str(),"r");
				while(fgets(buffer, sizeof(buffer), ptr)!=NULL)  // for each line in the file
				{
					if(strcmp(buffer,"\n")==0) break;
					b_buf1=strtok(buffer,",");  // the roll number
					b_buf2=strtok(buffer,",");  // the name 
					b_buf3=strtok(buffer,"\n");   // the webmail id
					student_roll_name[b_buf1]=b_buf2;
					student_course_list[b_buf1].push_back(course_code);
					course_student_list[course_code].push_back(b_buf1);
				}
				fclose(ptr);

			}
		}
		closedir(dir);
	}

	char* memory_map1;  // to store the current file
	int* memory_map2;  // to store if the data is available or not -> 0  = control of parent  , 1 = control of child
	char* curr_file;    // to store the location of the current file
	int* terminate;    // if  this is 1 then it means no more files are left-> lets terminate the process
	int file_size;  // the size of the current file

	terminate = (int*) mmap( NULL, sizeof(int), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1 , 0 );
	*terminate= 0;
	curr_file = (char*)mmap( NULL, 200, PROT_READ | PROT_WRITE, MAP_SHARED| MAP_ANONYMOUS , -1 , 0 );
	memory_map2 = (int*) mmap ( NULL , sizeof(int) , PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1 , 0 );
	*memory_map2 = 0; 


	if( fork()==0 ) 
	{
		// THis is the child process
		cout<<"THis is the child process"<<endl;
		while( *terminate == 0 )  // while termination is signalled by the parent 
		{
			while( *memory_map2 == 0 ); // wait for parent to give control


			ptr = fopen((char*)curr_file,"r");
			cout<<"CHILD: "<< curr_file<<endl;
			fseek( ptr, 0L, SEEK_END );
			file_size = ftell( ptr );
			fseek( ptr, 0L, SEEK_SET );
			memory_map1 = (char*)mmap( NULL,  file_size , PROT_READ , MAP_SHARED, fileno(ptr), 0 );
			//cout<< memory_map1<<endl;

			int i=0;
			int j=0;

			// get the list of roll numbers in the file
			vector<string> student_list; // the list of students who are in the current list
			while ( i< file_size )
			{
				j=0;
				while( memory_map1[i] != ',' )
				{	
					buffer[j++] = memory_map1[i++];
				}
				buffer[j++]='\0';
				while( memory_map1[i] != '\n' )
				{
					i++;
				}
				i++;
				student_list.push_back( string(buffer ) );
				
			}
			munmap ( memory_map1  , file_size);
			memory_map1 = (char*) mmap ( NULL, file_size*10 , PROT_WRITE, MAP_SHARED , fileno(ptr) , 0 );

			char* s_ptr= memory_map1 ;  // the pointer to the string
			

			// now start writing the data
		//	map<string, vector<string> >::iterator mit;
			vector<string>::iterator vit;   // iterate over the students in the  file
			vector<string>::iterator vit2;  // iterate over courses for the students
			for( vit = student_list.begin() ; vit != student_list.end() ; vit++ ) 
			{
				cout<< "STUDENT list Iterator "<<endl;
				// TODO : write the data back to the file

				// write the roll no. first
				for( i = 0 ; i < (*vit).size()  ; i++, s_ptr++)
				{
					cout<<"HERE : "<<(*vit)[i]<<endl;
					*s_ptr = (*vit)[i]; 
					cout<<"HERE"<<endl;
				}
				*s_ptr= ',';
				s_ptr++;


				cout<< "STUDENT list Iterator "<<endl;
				for( vit2 = student_course_list[*vit].begin() ; vit2!= student_course_list[*vit].end() ; vit2++ )
				{
					for( i= 0 ; i < (*vit2).size() ; i++ , s_ptr++ )
					{
						*s_ptr = (*vit2)[i];
					}
					*s_ptr = ',';
					s_ptr++;

				}
				*s_ptr = '\n';
				cout<< "STUDENT list Iterator "<<endl;
				s_ptr ++;
			}

			munmap ( memory_map1  , file_size*10);

			fclose( ptr); 

			*memory_map2 = 0; // pass control to parent
		}
		cout<<"CHild process ends" <<endl;

	}
	else
	{
		// This is the parent process
		cout<<"THis is the parent process"<<endl;
		for(it = dept_folder_list.begin() ; it!= dept_folder_list.end() ; it++ )
		{
			dir = opendir( (b_base + (*it)).c_str() );   // open the directory of the current directory
			while(( files=readdir(dir))!=NULL)    // for all the files in the dept.
			{
				if( strcmp(files->d_name,"..")!=0 && strcmp(files->d_name,".") )
				{
					while(  *memory_map2 ==1 ) ;  // for the child to give control

					curr_course = b_base + (*it) +string("/")+ string(files->d_name);
					course_code = string(files->d_name).substr(0,5);
	
					ptr = fopen(curr_course.c_str(),"r");
					fseek( ptr, 0L, SEEK_END );
					file_size = ftell( ptr );
					fseek( ptr, 0L, SEEK_SET );
					memory_map1 = (char*) mmap( NULL,  file_size , PROT_READ , MAP_SHARED, fileno(ptr), 0 );

					strcpy ( curr_file, curr_course.c_str() );  // tell the current file to the child process
			//		cout<<"PARENT : "<< curr_file<<endl;

					munmap ( memory_map1,  file_size );
					*memory_map2=  1;  // pass control to child

					while( *memory_map2 == 1 );  // while the child is working

					//munmap ( memory_map1,  file_size );
		//			*terminate =1 ;  // For testing purpose only on one file

					fclose(ptr);
		
				}
			}
			closedir(dir);
		}
		*terminate =1 ;  // For testing purpose only on one file
		cout<<"parent process ends"<<endl;


	}



	return 0;
}
