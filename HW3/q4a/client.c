//client for p3 part a

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/mman.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s file-to-read\n", argv[0]);
		exit(1);
	}

	const int FILESIZE = sizeof(char) + sizeof(int);
	const char FILENAME[] = "temp.bin";
	int fd = open(FILENAME, O_RDWR|O_CREAT|O_TRUNC, 0600);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	int* count = (int *)mmap(NULL, FILESIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); 
	if (count == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	char* str = (char *)count + sizeof(int);
	FILE* sourceFile = fopen(argv[1], "r");
	if (sourceFile == NULL) {
		perror(argv[1]);
		exit(1);
	}
	char* line;
	size_t len = 0;
	while (getline(&line, &len, sourceFile) != -1) {
		strcpy(str, line);
		(*count)++; 

		sleep(1);
	}
	munmap(count, FILESIZE);
	close(fd);
	fclose(sourceFile);
}
