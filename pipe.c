#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	//need to implement special no args exit
	if (argc < 2) {
        printf("No arguments provided.\n");
        return EINVAL;
    } 

	//case if only one argument -- reduces complexity by just directly running execlp
	if(argc == 2){
		execlp(argv[1], argv[1], NULL);
		exit(0);
	}

	//create pipefd array and pipe
	int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Pipe error");
        return 1;
    } 

	

	//label pipe ends 
	int read_end = pipefd[0];
	int write_end = pipefd[1];

	//first process - take in std input, output to write end of pipe
	//middle processes - take in from read end, output to write end of pipe
	//last process - take in from read end, output to standard output

	//for every p processes, there is p-1 pipes
	//for i = 1, i < argc - 1, i++



	//iterate through the arguments
	for(int i = 1; i <= argc - 1; i++){
		int child_code = fork(); //fork


		if(child_code == 0){
			printf("We are in the child process!\n");
			printf("Argument # %d\n", i);
			dup2(write_end, STDOUT_FILENO); //redirect output to the write end of pipe
			close(read_end);
			close(write_end);
			execlp(argv[i], argv[i], NULL);
			perror("exec");
            	_exit(1); 
			exit(0);//dont know if i need this

		} else if(child_code > 0){
			printf("We are in the parent process!\n");
			printf("Let's let the kid do the work:\n");
			dup2(read_end, STDIN_FILENO); //this is redirecting 0 (input) to the read end of the pipe
			close(write_end);
			int status = 0;
			//add some wifexited type shit
			waitpid(child_code, &status, 0);
			close(read_end);// Close the read end of the pipe in the parent process

		} else {
			printf("Child process creation error!");
		}
	}
	

	printf("All done!\n");
	return 0;
}
