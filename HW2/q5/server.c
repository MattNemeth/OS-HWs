//server program for problem 5

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>

int main() {
	const int FILESIZE = sizeof(char) + sizeof(int);
	const char FILENAME[] = "temp.bin";

	int fd = open(FILENAME, O_RDWR|O_CREAT|O_TRUNC, 0600);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	int result = lseek(fd, FILESIZE - 1, SEEK_SET);
	if (result == -1) {
		perror("lseek");
		exit(1);
	}

	result = write(fd, "", 1);
	if (result != 1) {
		perror("write");
		exit(1);
	}

	int* count = (int *)mmap(NULL, FILESIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (count == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	char* str = (char *)count + sizeof(int);

	int old = *count;
	while (1) {
		if (old != *count) {
			old = *count;
			if (strcmp(str, "Stop\n") == 0) {
				break;
			}
			printf("%s", str); // print the string
		}
	}

	munmap(count, FILESIZE);
	close(fd);
	remove(FILENAME);
}
