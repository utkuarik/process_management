
#include <stdio.h>
#include<iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>
#include <csignal>
#include <sys/stat.h>
#include <fcntl.h>
#include <map>
#include <vector>
using namespace std;




int main(int argc, char *argv[]) 
{ 

vector<string> file_content;
fstream process_file ("./pr_output.txt", fstream::out | fstream::app);

string line;
char* child_process = argv[1];




// cout << argv[1]<<" is waiting for a signal"<<endl;


cout<<"file created"<<endl;
while (!process_file.eof())
{
	
	getline (process_file,line);   
	cout<<line<<endl;
	file_content.push_back(line);    
}
process_file.close();

for(int i=0; i < file_content.size(); i++){

	cout << file_content.at(i)<< endl;
	process_file<<file_content.at(i)<<endl;
}


process_file.open("./pr_output.txt", fstream::out | fstream::app);
cout<<"yesssss"<<endl;
process_file << argv[1]<<" is waiting for a signal"<<endl;
cout << argv[1]<<" is started and it has a pid of "<<to_string(getpid())<<endl;



return 0;


}

