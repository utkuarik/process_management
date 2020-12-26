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
    vector<int> pidList;
    pid_t pid ;
    char *myfifo = (char*) "/tmp/myfifo";

    int namedpipe = open(myfifo, O_WRONLY);
    fstream watchdog_file(argv[3], ios::out);
    fstream process_file (argv[2], ios::out);

    // Add watchdog to pipe 
    string  msg;
    msg =  "P0 "  + to_string(getpid());
    cout << msg << endl;
    write(namedpipe, msg.c_str(), strlen(msg.c_str())+1); 
    

    int number_of_processes = stoi(argv[1]);
    for(int i=1 ; i<=number_of_processes; i++) // loop will run n times (n=5) 
    { 
        pid = fork();
        if(pid == 0) 
        {
            pidList.push_back(getpid());
            msg =  "P" + to_string(i) + " " + to_string(getpid());
            cout << msg << endl;
            string temp = "P" + to_string(i);
            const char *child_process = temp.c_str();
            write(namedpipe, msg.c_str(), strlen(msg.c_str())+1); 

            cout<<"P"<<i<<" is started and it has a pid of "<<to_string(getpid())<<endl;
            watchdog_file << "P"<<i<<" is started and it has a pid of "<<to_string(getpid())<<endl;


            cout<< child_process << endl;
            int k = execlp("./process", "./process", child_process, argv[2], NULL);
            cout<<k<<endl;
            return 0;
        }
    }
    int count = 0; 
    while(count < 5) {
        int deadChildPid = wait(NULL); /* parent will wait for the child to complete */ 
        cout << "dead pid:" <<deadChildPid<< endl;
        count++;
    }
} 

