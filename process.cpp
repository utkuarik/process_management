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

string p_id ;
fstream process_file ;


// define signal handlers
void sighup_handler(int sighup) 
{
    signal(SIGHUP, sighup_handler ); /* reset signal */
    cout<<p_id<< " received signal " << sighup<< endl;
    process_file <<p_id<< " received signal " << sighup<<endl;
} 
  
// sigint() function definition 
void sigint_handler(int sigint) 
{ 
    signal(SIGINT, sigint_handler); /* reset signal */
    cout<<p_id<< " received signal " << sigint<< endl;
    process_file <<p_id<< " received signal " << sigint<<endl;
} 
  
// sigquit() function definition 
void sigterm_handler(int sigterm) 
{   
    signal(SIGTERM, sigterm_handler);
    cout<<p_id<< " received signal " << sigterm<< endl;
    process_file <<p_id<< " received signal " << sigterm<<endl;
    exit(0); 
} 

void sigill_handler(int sigill) 
{   
    signal(SIGILL, sigill_handler);
    cout<<p_id<< " received signal " << sigill<< endl;
    process_file <<p_id<< " received signal " << sigill<<endl;

} 

void sigtrap_handler(int sigtrap) 
{   
    signal(SIGTRAP, sigtrap_handler);
    cout<<p_id<< " received signal " << sigtrap<< endl;
    process_file <<p_id<< " received signal " << sigtrap<<endl;

} 

void sigfpe_handler(int sigfpe) 
{   
    signal(SIGFPE, sigfpe_handler);
    cout<<p_id<< " received signal " << sigfpe<< endl;
    process_file <<p_id<< " received signal " << sigfpe<<endl;

} 

void sigsegv_handler(int sigsegv) 
{   
    signal(SIGSEGV, sigsegv_handler);
    cout<<p_id<< " received signal " << sigsegv<< endl;
    process_file <<p_id<< " received signal " << sigsegv<<endl;

} 

void sigxcpu_handler(int sigxcpu) 
{   
    signal(SIGXCPU, sigxcpu_handler);
    cout<<p_id<< " received signal " << sigxcpu<< endl;
    process_file <<p_id<< " received signal " << sigxcpu<<endl;

} 

int main(int argc, char *argv[]) 
{ 
    vector<string> file_content;
    process_file.open(argv[2],ios::app);
    p_id = argv[1];
    sigset_t   set;
    int sig1;

    string line;
    char* child_process = argv[1];

    process_file << argv[1]<<" is waiting for a signal"<<endl;
    cout << argv[1]<<" is waiting for a signal "<<endl;


    signal(SIGHUP, sighup_handler); 
    signal(SIGINT, sigint_handler); 
    signal(SIGTERM, sigterm_handler); 
    signal(SIGILL, sigill_handler); 
    signal(SIGTRAP, sigtrap_handler); 
    signal(SIGFPE, sigfpe_handler); 
    signal(SIGSEGV, sigsegv_handler); 
    signal(SIGXCPU, sigxcpu_handler); 
    while(1)
        sigwait(&set, &sig1);
    return 0;

}




