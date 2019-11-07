#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(){
	int status;
	char *argv[]={"ll","-a",NULL};
	pid_t new_pid,pr;
	new_pid=fork();
	if(new_pid<0)
		printf("failed to create a child process!\n");
	else if(new_pid==0){
		printf("This is child process with pid of %d.\n",getpid());
		//execl("/bin/ls","ls","-l",NULL);
		exit(3);
	}
	else{
		pr=wait(&status);
		if(WIFEXITED(status)){
			printf("this child process %d exit normally.\n",pr);
			printf("the return code is %d .\n",WEXITSTATUS(status));		}
		else 
			printf("the child process %d exit abnormally.\n",pr);
	}
	return 0;
}
