#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	//need to implement special no args exit
	//this iterates through processes correctly
	//need to add dup2 use, wait, close
	for(int i = 1; i < argc; i++){
		int child_code = fork();
		if(child_code == 0){
		printf("We are in the child process!\n");
		printf( "Now running input: %d\n", i);
		execlp(argv[i], argv[i], NULL);
		} else if(child_code > 0){
		printf("We are in the parent process!\n");
		printf("Let's let the kid do the work:\n");
		} else {
		printf("Child process creation error!");
		}
	}
	printf("All done!\n");
	printf("Total inputs: %d\n", argc);
	return 0;
}
