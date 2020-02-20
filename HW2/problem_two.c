//Problem One

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
	FILE * fp1 = popen("find . -name '*.c'","r");
	FILE * fp2 = popen("tr a-z A-Z","r");

	char buf[20];
	while(fgets(buf, 20, fp1) != NULL){
		if(fp1 == 0){
			printf("There was an error with the popen command...\n");
		}else{
			printf("%s", buf);	
		}
	}
	return 0;
}
