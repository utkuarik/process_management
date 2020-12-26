#include <stdio.h>
#include<iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <csignal>
#include <sys/stat.h>
#include <fcntl.h>
#include <map>
#include <vector>
#include <signal.h> 

using namespace std;

// define signal handlers
void sighup_handler(int sighup) 
{ 
    signal(SIGHUP, sighup_handler ); /* reset signal */
    printf("CHILD: I have received a SIGHUP\n"); 
} 
  
// sigint() function definition 
void sigint_handler(int sigint) 
{ 
    signal(SIGINT, sigint_handler); /* reset signal */
    printf("CHILD: I have received a SIGINT\n"); 
} 
  
// sigquit() function definition 
void sigquit_handler(int sigquit) 
{   
    signal(SIGINT, sigquit_handler);
    printf("My DADDY has Killed me!!!\n"); 
    exit(0); 
} 



int main(int argc, char *argv[]) 
{ 
    vector<string> file_content;
    fstream process_file (argv[2], fstream::app);

    string line;
    char* child_process = argv[1];

    cout<<"file created"<<endl;
    while (!process_file.eof())
    {
        
        getline (process_file,line);   
        cout<<line<<endl;
        file_content.push_back(line);    
    }

    for(int i=0; i < file_content.size(); i++){

        cout << file_content.at(i)<< endl;
        process_file<<file_content.at(i)<<endl;
    }

    process_file << argv[1]<<" is waiting for a signal"<<endl;
    cout << argv[1]<<" is started and it has a pid of "<<to_string(getpid())<<endl;


    signal(SIGHUP, sighup_handler); 
    signal(SIGINT, sigint_handler); 
    signal(SIGQUIT, sigquit_handler); 
    for (;;) ; /* loop for ever */
    return 0;

}




