//Problem One

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
	FILE * fp1 = popen("find . -name '*.c'","r");
	FILE * fp2 = popen("tr a-z A-Z","w");

	const int bufSize = 100;
	char buf1[bufSize];

	while(fgets(buf1, bufSize, fp1) != NULL){
		fputs(buf1, fp2);
	}
	fclose(fp1);
	fclose(fp2);
}
