//server program for problem 4

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

int main() {
	const int SHM_SIZE = 1024;
	const char filename[] = "shm.dat";

	key_t key = ftok(filename, 1);
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

	char* line = (char *)count + sizeof(int);
	int old = *count;
	while (1) {
		if (old != *count) {
			old = *count; // update the count
			if (strcmp(line, "Stop\n") == 0) {
				break;
			}
			printf("%s", str);
		}
	}

	shmctl(shmid, IPC_RMID, NULL);
}
