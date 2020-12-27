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
        string pidName = "P" + to_string(i);
        pid = fork();
        if(pid == 0) 
        {
            msg =  pidName + " " + to_string(getpid());
            write(namedpipe, msg.c_str(), strlen(msg.c_str())+1); 
            cout<<pidName<<" is started and it has a pid of "<<to_string(getpid())<<endl;
            watchdog_file <<pidName<<" is started and it has a pid of "<<to_string(getpid())<<endl;
            execlp("./process", "./process", pidName.c_str(), argv[2], NULL);
            return 0;
        } else {
            pid_dict.insert ( pair<string,string>(pidName, to_string(pid)));
        }
    }
 
    while(1) {
        int deadChildPid = wait(NULL);  
        for (pair<std::string, string> element : pid_dict){
            string pidName = element.first;
            string temp_p_id = element.second;
            if(temp_p_id == to_string(deadChildPid)){
                // If a child dead
                pid = fork();
                if(pid == 0) 
                {
                    pid_dict.insert ( pair<string,string>(pidName, to_string(getpid())));
                    msg =  pidName + " " + to_string(getpid());
                    write(namedpipe, msg.c_str(), strlen(msg.c_str())+1); 
                    cout<<pidName<<" is started and it has a pid of "<<to_string(getpid())<<endl;
                    watchdog_file <<pidName<<" is started and it has a pid of "<<to_string(getpid())<<endl;
                    execlp("./process", "./process", pidName.c_str(), argv[2], NULL);
                    return 0;
                }  else {
                    pid_dict.insert ( pair<string,string>(pidName, to_string(pid)));
                }
                break;
            }
        }
    }
}
