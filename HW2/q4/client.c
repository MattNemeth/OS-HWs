#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/shm.h>

void makeupper(char* str) {
	while (*str) {
		*str = toupper((unsigned char) *str);
		str++;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s file-to-read\n", argv[0]);
		exit(1);
	}

	const int SHM_SIZE = 1024;
	const char FILENAME[] = "shm.dat";

	key_t key = ftok(FILENAME, 1);
	if (key == -1) {
		perror("ftok");
		exit(1);
	}

	int shmid = shmget(key, SHM_SIZE, 0644|IPC_CREAT);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}

	int* count = (int *)shmat(shmid, (void *)0, 0);
	if (count == (int *)-1) {
		perror("shmat");
		exit(1);
	}

	char* str = (char *)count + sizeof(int);
	*count = 0;
	char* line;
	size_t len = 0;

	FILE* sourceFile = fopen(argv[1], "r");
	if (sourceFile == NULL) {
		perror(argv[1]);
		exit(1);
	}

	while (getline(&line, &len, sourceFile) != -1) {
		makeupper(line); 
		strcpy(str, line);
		(*count)++;

		sleep(1);
	}

	strcpy(str, "Stop\n");
	(*count)++;
	shmdt(str);
}
