//Client program for problem 3

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void myToupper(char* str) {
	while (*str) {
		*str = toupper((unsigned char) *str);
		str++;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Invalid number of arguments. Usage: %s file-to-read\n", argv[0]);
		exit(1);
	}

	//open file user passed in
	FILE* sourceFile = fopen(argv[1], "r");
	if (sourceFile == NULL) {
		perror(argv[1]);
		exit(1);
	}

	//open pipe named myfifo
	char* fifo = "myfifo";
	mkfifo(fifo, 0666);
	int fd = open(fifo, O_WRONLY);

	char* line;
	size_t len = 0;

	//read everyting in the file. make letters uppercase. write to fifo
	while (getline(&line, &len, sourceFile) != -1) {
		myToupper(line); 
		write(fd, line, len);
		sleep(1);//pause for 1 second 
	}
	//file has been read. send stop
	write(fd, "Stop\n", 6);
	close(fd);
	fclose(sourceFile);
}
