// server for p3 part b

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main() {
	const int FILESIZE = sizeof(char) + sizeof(int);
	const char FILENAME[] = "temp.bin";
	const char SEM_FILENAME[] = "sem-key.bin";
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

	key_t SEM_KEY = ftok(SEM_FILENAME, 1);
	if (SEM_KEY == -1) {
		perror("ftok");
		exit(1);
	}

	int semid = semget(SEM_KEY, 1, 0660|IPC_CREAT);
	if (semid == -1) {
		perror("semget");
		exit(1);
	}

	union semun {
		int val;
	} arg;
	arg.val = 1;

	int semcontrol = semctl(semid, 0, SETVAL, arg);
	if (semcontrol == -1) {
		perror("semctl");
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
			printf("%s", str);
			if (strcmp(str, "Stop\n") == 0) {
				break;
			}
		}
	}
	munmap(count, FILESIZE);
	semctl(semid, 0, IPC_RMID, 0);
	close(fd);
	remove(FILENAME);
}
