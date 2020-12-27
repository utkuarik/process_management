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
    map<string,string> pid_dict;
    pid_t pid ;
    char *myfifo = (char*) "/tmp/myfifo";

    int namedpipe = open(myfifo, O_WRONLY);
    fstream watchdog_file(argv[3], ios::out);
    fstream process_file (argv[2], ios::out);

    // Add watchdog to pipe 
    string  msg;
    string p_id;
    msg =  "P0 "  + to_string(getpid());
    cout << msg << endl;
    string pid_no = to_string(getpid());
    write(namedpipe, msg.c_str(), strlen(msg.c_str())+1); 

    pid_dict.insert ( pair<string,string>("P0",pid_no));
    

    int number_of_processes = stoi(argv[1]);
    for(int i=1 ; i<=number_of_processes; i++) // loop will run n times (n=5) 
    { 
        pid = fork();
        if(pid == 0) 
        {
            pidList.push_back(getpid());
            msg =  "P" + to_string(i) + " " + to_string(getpid());
            // p_id = "P" + to_string(i);
            // pid_dict.insert ( pair<string,string>(p_id,to_string(getpid())));
            // cout << msg << endl;
            string temp = "P" + to_string(i);
            const char *child_process = temp.c_str();
            write(namedpipe, msg.c_str(), strlen(msg.c_str())+1); 

            cout<<"P"<<i<<" is started and it has a pid of "<<to_string(getpid())<<endl;
            watchdog_file << "P"<<i<<" is started and it has a pid of "<<to_string(getpid())<<endl;


            // cout<< child_process << endl;
            int k = execlp("./process", "./process", child_process, argv[2], p_id.c_str(), NULL);
            // cout<<k<<endl;
            // return 0;
        }
    }

    char temp[30];
    string p_index, p_pid;
    string id;
    string temp_pid;
    for (int i=0; i<=number_of_processes; i++) {
            read(namedpipe, temp, 30);
            stringstream splitmsg(temp);
            splitmsg >> p_index >> p_pid;
            id = (p_index.substr(1));
            temp_pid = p_pid;
            pid_dict.insert ( pair<string,string>(id,temp_pid));
    }

    int count = 0; 
    while(1) {
        int deadChildPid = wait(NULL);  
        // parent will wait for the child to complete  
        cout << "dead pid:" <<deadChildPid<< endl;

        for (pair<std::string, string> element : pid_dict){
            string no = element.first;
            // Accessing VALUE from element.
            string temp_p_id = element.second;
            cout<<no<<endl;
            cout<<temp_p_id<<endl;
            if(temp_p_id == to_string(deadChildPid)){
                // If a child dead
                pid = fork();
                if(pid >0) {
        
                msg =  no + " " + to_string(getpid());
                write(namedpipe, msg.c_str(), strlen(msg.c_str())+1); 
                cout<<no<<" is started and it has a pid of "<<to_string(getpid())<<endl;
                watchdog_file <<no<<" is started and it has a pid of "<<to_string(getpid())<<endl;
                }
            }
        }

        count++;
    }
} 

