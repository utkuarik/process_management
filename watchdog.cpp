
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
// #include <libexplain/execlp.h>
using namespace std;

// int main(int argc, char* argv[])
// {
//     pid_t child_pid;
//     int number_of_processes = stoi(argv[1]);
//     for(int i = 1; i <= number_of_processes; i++){                    
//         child_pid = fork();
//         if(child_pid <= 0){
//             break;
//         }


        
//     }

//     cout << i << " child process id: " << getpid()<< " " << "parent process id: "<< getppid() << endl;


// }

// int main (int argc, char *argv[]) {
//    pid_t childpid = 0; 
//    int i, n;
 
//    if (argc != 2){   /* check for valid number of command-line arguments */ 
//       fprintf(stderr, "Usage: %s processes\n", argv[0]);
//       return 1; 
//    }     
//    n = atoi(argv[1]);  
//     for (i = 1; i < n; i++)
//       if ((childpid = fork()) <= 0)
//          break;
 
//     fprintf(stderr, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
//            i, (long)getpid(), (long)getppid(), (long)childpid);
//    return 0; 
// }

int main(int argc, char *argv[]) 
{ 

    pid_t pid ;
    char * myfifo = (char*) "/tmp/myfifo";

    int namedpipe = open(myfifo, O_WRONLY);
    int fd;
    char arr1[80], arr2[80];

    ofstream myfile (argv[3]);

    // Add watchdog to pipe 
    string  msg;
    msg =  "P0 "  + to_string(getpid());
    cout << msg << endl;
    write(namedpipe, msg.c_str(), strlen(msg.c_str())+1); 
    close(namedpipe);



    int number_of_processes = stoi(argv[1]);
    for(int i=1;i<=number_of_processes;i++) // loop will run n times (n=5) 
    { 
        pid = fork();
        if(pid == 0) 
        { 

            string  msg;
            msg =  "P" + to_string(i) + " " + to_string(getpid());
            cout << msg << endl;
            string temp = "P" + to_string(i);
            const char *child_process = temp.c_str();
            write(namedpipe, msg.c_str(), strlen(msg.c_str())+1); 
            close(namedpipe);
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            if (myfile.is_open()){
                myfile << "P"<<" "<<i<<" is started and it has a pid of "<<to_string(getpid())<<endl;
            }



            // Open FIFO for Read only 
            // fd = open(myfifo, O_RDONLY); 
      
            // // // Read from FIFO 
            // read(fd, arr1, sizeof(arr1)); 
      
            // // Print the read message 
            // printf("User2: %s\n", arr1); 
            cout<< child_process << endl;
            execlp("./process.out","./process.out", child_process, (char *)NULL);
            
            return 0;

            
        } 

        else if(pid > 0){

        // wait(NULL); /* parent will wait for the child to complete */ 
        printf("I am the parent process.\n");
        }
    } 
    for(int i=0;i<number_of_processes;i++) // loop will run n times (n=5) 
    wait(NULL); 
      
} 

