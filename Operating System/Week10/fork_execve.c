#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  pid_t pid = fork();
	if (pid == 0) {
		printf("I'm child process.\n");
		/* call 'execve' system call
		 * int execve(const char *filename, char *const argv[], char *const envp[]);
		 * you can use 'man execve' command to get more information
		 */
		char *args[] = {"/bin/ls", NULL};
		/*execve*/
    char *arg[] = {"ls","-l","/etc/passwd",NULL};
    char *envp[] = { "PATH=/bin",0 };
    execve(args[0],arg,envp);
		perror("Call execve failure!!\n");
		/*exit*/
    exit(0);
	} else {
		printf("I'm parent process.\n");
		exit(-1);
	}
	return 0;
}