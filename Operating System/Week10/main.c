/*
create a child process;
values for return:child process return 0,parent process return ID of child process
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void){
        pid_t new_pid;
        new_pid=fork();
        switch(new_pid){
                case 0:{printf("PID is %d,",getpid());
                        printf("PPID is %d\n",getppid());
                        break;}
                case -1:{printf("failed to create a child process!\n");
                         break;}
                }
        return 0;
}

