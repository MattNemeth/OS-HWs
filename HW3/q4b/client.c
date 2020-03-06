//client for p3 part b

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s file-to-read\n", argv[0]);
		exit(1);
	}

	const int FILESIZE = sizeof(char) + sizeof(int);
	const char FILENAME[] = "temp.bin";
	const char SEM_FILENAME[] = "sem-key.bin";
	struct sembuf WAIT[1], SIGNAL[1];
	WAIT[0].sem_num = 0;
	WAIT[0].sem_op = -1;
	WAIT[0].sem_flg = SEM_UNDO;

	SIGNAL[0].sem_num = 0;
	SIGNAL[0].sem_op = 1;
	SIGNAL[0].sem_flg = SEM_UNDO;

	key_t SEM_KEY = ftok(SEM_FILENAME, 1);
	if (SEM_KEY == -1) {
		perror("ftok");
		exit(1);
	}

	int semid = semget(SEM_KEY, 1, 0660);
	if (semid == -1) {
		perror("semget");
		exit(1);
	}
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
	semop(semid, WAIT, 1);
	while (getline(&line, &len, sourceFile) != -1) {
		strcpy(str, line);
		(*count)++; 
		sleep(1);
	}
	semop(semid, SIGNAL, 1);
	munmap(count, FILESIZE);
	close(fd);
	fclose(sourceFile);
}
