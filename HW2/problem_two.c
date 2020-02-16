// this is for problem two

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h> 
#include <sys/wait.h>
#include <sys/types.h>

void printFunction(char* fileName){
	printf("Main process. PID is %d\n", getpid()); //display this once then wait for children to die
	printf("\n ls command: \n");
	int p_id = (int)fork();
	if(p_id == 0){
		char* binarypath = "/bin/ls";
		char* arg0 = "ls";
		char* arg1 = "-l";
		char* arg2 = fileName;

		execl(binarypath, arg0, arg1, arg2, NULL);	
		exit(0);
	}else{
		wait(0);
		printf("\n ps command: \n");
		int p_id2 = (int)fork();
		if(p_id2 == 0){
			char* binarypath = "/bin/ps";
			char* arg0 = "ps";
			char* arg1 = "-ef";

			execl(binarypath, arg0, arg1, NULL);	
			exit(0);
		}else{
			wait(0);
			printf("\n more command: \n");
			int p_id3 = (int)fork();
			if(p_id3 == 0){
				char* binarypath = "/bin/more";
				char* arg0 = "more";
				char* arg1 = fileName;

				execl(binarypath, arg0, arg1, NULL);	
				exit(0);
			}else{
				wait(0);
				printf("Main process terminated...\n");
				}
			}
		}
	return;
}

int main(int argc, char* argv[]){
	if(argc > 2){
		printf("Too many arguments...\n");
		exit(0);
	}else if(argc < 2){
		printf("Too few arguments...\n");
		exit(0);
	}else{
		printFunction(argv[1]);
	}
	return 0;
}

