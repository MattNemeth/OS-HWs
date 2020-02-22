#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/shm.h>

// Helper function to convert a string to upper case.
//   Loops through the characters of a string and makes them uppercase
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

	// Generate a key
	key_t key = ftok(FILENAME, 1);
	if (key == -1) {
		perror("ftok");
		exit(1);
	}

	// Connect to and create the shared memory space
	int shmid = shmget(key, SHM_SIZE, 0644|IPC_CREAT);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}

	// Attach to memory segment
	int* count = (int *)shmat(shmid, (void *)0, 0);
	if (count == (int *)-1) {
		perror("shmat");
		exit(1);
	}

	// Create a reference for where to store the string
	char* str = (char *)count + sizeof(int);
	*count = 0;

	// Open the text file
	FILE* sourceFile = fopen(argv[1], "r");
	if (sourceFile == NULL) {
		perror(argv[1]);
		exit(1);
	}

	// Begin reading the lines from the source file
	char* line;
	size_t len = 0;

	while (getline(&line, &len, sourceFile) != -1) {
		makeupper(line); // convert to uppercase
		strcpy(str, line); //move the line to the memory for the string
		(*count)++; // update the count

		sleep(1);
	}

	// Send signal to the server to die
	strcpy(str, "Stop\n");
	(*count)++;

	// Detach segments
	shmdt(str);
}
