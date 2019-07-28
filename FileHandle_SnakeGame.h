#include<fstream>
#include<iostream>
#include<cstdio>
using namespace std;

void file_handle(fstream &fs,int &first_time,int &score,int &flag)
{
	int f_score,clear_file;
	char str[100];
	
	//file must be opened only once
	if(first_time==0)
		fs.open("scores.txt",ios::in | ios::out | ios::app);
	
	if(!fs)
	{
		cout<<"\nRecords can't be written in file !!\n";
		cout<<"Game is terminated due to some fault ...\n";
		exit(1);
	}
	
	//for first time, write the score in file first and then read back from file
	if(first_time==0)
	{
		fs<<score<<endl;
		first_time=1;
	}
		
	fs.seekg(0L,ios::beg); //for reading, setting fs at beginning of file
	bool isHighest=true;
	while(!fs.eof())
	{
		fs.getline(str,100,'\n');
		sscanf(str,"%d",&f_score);
				
		if(score>=f_score)
			continue;
		if(score<f_score){
			isHighest=false;
			break;
		}	
	}
	if(isHighest==true)
		cout<<"\nCongratulations ! This is the new HIGHEST SCORE !!\a\n";
			
	fs.clear(); //so that opened file can be used as many times as required
	if(flag!=0)
	{
		fs.seekp(0L,ios::end); //writing scores at the end of the file
		fs<<score<<endl;
	}
	flag=1;
		
	cout<<"\nDo you want to remove all past scores? (1 for YES) : ";
	cin>>clear_file;
	if(clear_file==1)
	{
		fs.close();
		fs.open("scores.txt",ios::out | ios::trunc);
		fs.close();
		fs.open("scores.txt",ios::in | ios::out | ios::app); //again opening file
		cout<<"All past records deleted !!\n\n\a";
	}	
}

void file_close(fstream& fs)
{
	fs.close();
}
