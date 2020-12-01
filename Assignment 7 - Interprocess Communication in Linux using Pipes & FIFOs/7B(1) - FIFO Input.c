#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

// FIFOs have “names” and exist as special files within a file system. Hence called named pipes

int main()
{
	int ret = 0, f1 = 0, f2 = 0;
	char sentence[200], readSentence[1000];

	printf("Creating the FIFO 1\n");

	ret = mkfifo("myfifo", 0666);   // open a named pipe (pathname, mode)
	printf("\nEnter some text : \n");

	fgets(sentence, 200, stdin);

	printf("\nWriting the text into FIFO 1\n");

	f1 = open("myfifo", O_WRONLY);

    // O_RDONLY: read only, O_WRONLY: write only, O_RDWR: read and write, O_CREAT: create file if it doesn’t exist, O_EXCL: prevent creation if it already exists

    write(f1, sentence, strlen(sentence)+1);
	printf("\nWaiting for the info through FIFO 2, going for sleep ...\n");
	sleep(5);

	f2 = open("myfifo", O_RDONLY);
	read(f2, readSentence, 1000);
	printf("\nThe info received from FIFO 2 : \n\n%s", readSentence);
	printf("\n\n");

	unlink("myfifo");
	return 0;
}
