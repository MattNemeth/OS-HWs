// this is for problem one

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h> 
#include <sys/wait.h>
#include <sys/types.h>

void printFunction(int N){
	int p_id = (int)fork();
	if(p_id == 0){
		for(int j=0;j<N;j++){
			printf("Child process. PID is %d. PPID is %d\n", getpid(), getppid());
			sleep(2);
		}
	}else{
		int p_id2 = (int)fork();
		if(p_id2 == 0){
			for(int k=0;k<N;k++){
				printf("Child process. PID is %d. PPID is %d\n", getpid(), getppid());
				sleep(2);
			}
		}else{
			int p_id3 = (int)fork();
			if(p_id3 == 0){
				for(int z=0;z<N;z++){
					printf("Child process. PID is %d. PPID is %d\n", getpid(), getppid());
					sleep(2);
				}
			}else{
				for(int i=0;i<N;i++){
					printf("Main process. PID is %d\n", getpid());
					sleep(2);
				}
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
	}else if(!isdigit(*argv[1])){
		printf("The argument passed in must be an integer...\n");
		exit(0);
	}else{
		printFunction(atoi(argv[1]));
	}
	return 0;
}

