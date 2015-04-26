#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<dirent.h>
#include<cstring>
#include<set>
#include<vector>
#include<string>
#include<map>
using namespace std;



vector<string> dept_folder_list;   // a list of all the dept-> used to traverse the folder
map<string,string>  course_list;    // a mapping from the course code to the course name
map<string,vector<string> >  course_student_list;        // a mapping from the course to the vector of students who are attending that course
map<string,vector<string> >  student_course_list;     // a mapping from the student roll_no to the list of courses he is takign
map<string,string>  student_roll_name;      // a mapping of the student roll_no to the student names

map<string,FILE* > dept_name_file;

char buffer[1000];
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

	FILE* cs=fopen("cse.txt","w");
	FILE* ec=fopen("ece.txt","w");
	FILE* me=fopen("me.txt","w");
	FILE* ce=fopen("ce.txt","w");
	FILE* dd=fopen("dd.txt","w");
	FILE* bt=fopen("bt.txt","w");
	FILE* cl=fopen("cl.txt","w");
	FILE* ee=fopen("eee.txt","w");
	FILE* ep=fopen("ep.txt","w");
	FILE* ct=fopen("ct.txt","w");
	FILE* mc=fopen("mc.txt","w");
	FILE* hs=fopen("hs.txt","w");



	map<string,string>::iterator mit;
	
	for(mit= student_roll_name.begin(); mit!=student_roll_name.end(); mit++)
	{
		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "01") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "01") ==0  )  )   // 
		{
			fprintf(cs, "*********************************************************\n");
			fprintf(cs, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(cs, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(cs,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}


		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "02") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "02") ==0  )  )   // 
		{
			fprintf(ec, "*********************************************************\n");
			fprintf(ec, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(ec, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(ec,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}


		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "03") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "03") ==0  )  )   // 
		{
			fprintf(me, "*********************************************************\n");
			fprintf(me, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(me, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(me,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}


		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "04") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "04") ==0  )  )   // 
		{
			fprintf(ce, "*********************************************************\n");
			fprintf(ce, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(ce, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(ce,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}


		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "05") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "05") ==0  )  )   // 
		{
			fprintf(dd, "*********************************************************\n");
			fprintf(dd, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(dd, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(dd,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}


		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "06") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "06") ==0  )  )   // 
		{
			fprintf(bt, "*********************************************************\n");
			fprintf(bt, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(bt, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(bt,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}



		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "07") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "07") ==0  )  )   // 
		{
			fprintf(cl, "*********************************************************\n");
			fprintf(cl, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(cl, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(cl,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}



		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "08") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "08") ==0  )  )   // 
		{
			fprintf(ee, "*********************************************************\n");
			fprintf(ee, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(ee, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(ee,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}


		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "21") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "21") ==0  )  )   // 
		{
			fprintf(ep, "*********************************************************\n");
			fprintf(ep, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(ep, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(ep,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}

		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "22") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "22") ==0  )  )   // 
		{
			fprintf(ct, "*********************************************************\n");
			fprintf(ct, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(ct, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(ct,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}

		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "23") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "23") ==0  )  )   // 
		{
			fprintf(mc, "*********************************************************\n");
			fprintf(mc, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(mc, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(mc,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}


		if( (mit->first.c_str()[0]!='X' && strcmp( (mit->first).substr(4,2).c_str() , "41") == 0 ) || ( strcmp( (mit->first).substr(5,2).c_str(), "41") ==0  )  )   // 
		{
			fprintf(hs, "*********************************************************\n");
			fprintf(hs, "Roll No. : %s \n", mit->first.c_str() );
//			fprintf(cs, "Name :  %s \n", mit->second.c_str() );
			fprintf(hs, "COURSE LIST:  \n");
			for( it = student_course_list[ mit->first ].begin() ;  it!= student_course_list[ mit->first].end() ; it++ )
			{
				fprintf(hs,"\t%s \t %s \n", it->c_str(), course_list[*it].c_str() );
			}
		}





	}
	fclose(cs);
	fclose(ec);
	fclose(me);
	fclose(ce);
	fclose(dd);
	fclose(bt);
	fclose(cl);
	fclose(ee);
	fclose(ep);
	fclose(ct);
	fclose(mc);
	fclose(hs);



	return 0;
}
