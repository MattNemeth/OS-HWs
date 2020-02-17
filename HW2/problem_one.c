//Problem One

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

//first arg: command, example "/bin/ps"
//second arg: file, example "outputFile.txt"
//	stores the output of the command passed in as arg 1
//
int main(int argc, char* argv[]){
	if(argc > 3){
		printf("Too many arguments... Program only takes 2 input arguments.\n");
		exit(0);
	}else if(argc < 3){
		printf("Too few arguments... Program only takes 2 input arguments.\n");
		exit(0);
//	}else if(!isdigit(*argv[1])){
	//	printf("The argument passed in must be an integer...\n");
	//	exit(0);
	}else{
		int pid = fork();
		if(pid == 0){ // if pid = 0 we know its a child process
			int fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); 
			if(fd < 0){
				printf("There was an error opening the file.\n");
			}

			dup2(fd, 1);
			close(fd);

			execl(argv[1], argv[1], NULL); // execute the command that was passed in	
		}
	}
	return 0;
}

