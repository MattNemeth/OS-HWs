//Problem One

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
	FILE * fp = popen("ls","r");
	if(fp == 0){
		printf("There was an error with the popen command...\n");
	}else{
			
	}

	return 0;
}
