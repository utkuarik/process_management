
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
fstream process_file;

char* child_process = argv[1];
cout << argv[1]<<" is waiting for a signal"<<endl;


process_file.open("pr_output.txt");
string x;
while (process_file >> x) {
    file_content.push_back(x);
}

for(int i=0; i < file_content.size(); i++){

	cout << file_content.at(i)<< endl;
	process_file<<file_content.at(i);
}

if (process_file.is_open()){
    process_file << argv[1]<<" is started and it has a pid of "<<to_string(getpid())<<endl;
}

process_file.close();
return 0;


}

