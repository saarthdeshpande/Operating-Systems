#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>


int main()
{
	int f1 = 0, f2 = 0, i = 0, end = 0, ret = 0, eof=0;

	char readSentence[1000], buffer[1000], ch;
	int nChar = 0, nWords = 0, nLines = 0, nLetters = 0;
	FILE *fp;

	ret = mkfifo("myfifo", 0666);   // open a named pipe (pathname, mode)
	printf("\nWaiting to recieve text from FIFO 1 ...\n");
	sleep(5);

	f1 = open("myfifo", O_RDONLY);

    // O_RDONLY: read only, O_WRONLY: write only, O_RDWR: read and write, O_CREAT: create file if it doesn’t exist, O_EXCL: prevent creation if it already exists

    read(f1, readSentence, 1000);
	printf("\nRecieved text :\n\n%s\n", readSentence);
	int w = 0;

	for (i = 0; readSentence[i] != '\0'; i++) {
		if ((readSentence[i] == '.') || (readSentence[i] == '!') || (readSentence[i] == '?'))
			nLines++;
		else if (readSentence[i] == ' ' || readSentence[i] == ',' || readSentence[i] == ';' || readSentence[i] == '.')
			nWords++;
	}

	nChar = i - 1;
	nLetters = nChar - nWords - 1;

	fp = fopen("7b.txt", "w");

	fprintf(fp, "Number of characters : %d\n", nChar);
	fprintf(fp, "Number of Letters : %d\n", nLetters);
	fprintf(fp, "Number of Words : %d\n", nWords);
	fprintf(fp, "Number of Lines : %d\n", nLines);
	fclose(fp);
	fp = fopen("7b.txt", "r");
	i = 0;

	while (eof != -1) {
		eof = fscanf(fp, "%c", &ch);
		buffer[i] = ch;
		i++;
	}
	fclose(fp);

	printf("\nContents of the file :\n");
	printf("\n%s\n", buffer);

	printf("Writing above output to the FIFO 2 ...\n\n");

	f2 = open("myfifo", O_WRONLY);
	write(f2, buffer, strlen(buffer)+1);
	sleep(5);
	unlink("myfifo");
	return 0;
}