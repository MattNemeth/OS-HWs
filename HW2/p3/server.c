#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	// Open the fifo
	char* fifo = "myfifo";
	mkfifo(fifo, 0666);
	
	int fd = open(fifo, O_CREAT | O_RDONLY);
	char buffer[100];

	// Read contents of fifo. Print out what is read. Look for stop.
	while (1) {
		read(fd, buffer, sizeof(buffer));
		if (strcmp(buffer, "Stop\n") == 0) {
			break;
		}
		printf("%s", buffer);
	}
	//close fifo
	close(fd);
	unlink(fifo);
}
