#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

	// first process - take in std input, output to write end of pipe
	// middle processes - take in from read end, output to write end of pipe
	// last process - take in from read end, output to standard output

	// for every p arguments, there are p-1 pipes
	// for every p arguments, there are p forks!!!


int main (int argc, char* argv[]) {
	
	//special no argument case, exit immediately
	if (argc < 2) {
        printf("No arguments provided.\n");
		errno = EINVAL;
        exit(errno);
    } 

	//create int i to track arguments 
    int i;

	//iterate through arguments 
    for(i = 1; i < argc - 1; i++) {
        int pipefd[2]; //create pipefd array
        pipe(pipefd); //create pipe!

        if (!fork()) { //if fork() does not return a negative number (aka it works)
            dup2(pipefd[1], STDOUT_FILENO); // redirect std output to the 'write' end of the pipe
			close(pipefd[0]); //close the read end
			close(pipefd[1]); //close the write end
            execlp(argv[i], argv[i], NULL); //execute the first passed-in program

			//if execlp returns, there was an execution error, exit
            perror("exec"); 
			errno = ENOEXEC;
            exit(errno); 
        }

        // redirect std input to the 'read' end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]); //close the read end
        close(pipefd[1]); //close the write end

		
		//status variable to keep track
		int status;

		//call waitpid to wait for child processes (no orphans), else exit
        if (waitpid(-1, &status, 0) == -1) { 
            perror("waitpid");
			errno = ECHILD;
            exit(errno);
        }
    }

	//outside loop, to execute the final argument!
    execlp(argv[i], argv[i], NULL);

	//if cannot execute, exit 
    perror("exec");
	errno = ENOEXEC;
    exit(errno);
}
