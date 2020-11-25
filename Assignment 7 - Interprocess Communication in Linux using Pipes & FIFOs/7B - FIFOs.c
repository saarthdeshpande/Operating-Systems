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

	ret = mkfifo("myfifo", 0666);
	
	sleep(5);

	f1 = open("myfifo", O_RDONLY);

	read(f1, readSentence, 1000);
	printf("\nRECIEVED TEXT: :\n\n%s\n", readSentence);
	int w = 0;

	for (i=0; readSentence[i] != '\0'; i++)
	{
		if ((readSentence[i] == '.') || (readSentence[i] == '!') || (readSentence[i] == '?'))
			nLines++;
		else if (readSentence[i] == ' ' || readSentence[i] == ',' || readSentence[i] == ';' || readSentence[i] == '.')
			nWords++;
	}

	nChar = i - 1;
	nLetters = nChar - nWords - 1;

	fp = fopen("7b.txt", "w");

	fprintf(fp, "CHARACTERS IN TEXT : %d\n", nChar);
	fprintf(fp, "LETTERS IN TEXT : %d\n", nLetters);
	fprintf(fp, "WORDS IN TEXT : %d\n", nWords);
	fprintf(fp, "SENTENCES IN TEXT : %d\n", nLines);
	fclose(fp);
	fp = fopen("7b.txt", "r");
	i = 0;

	while (eof != -1)
	{
		eof = fscanf(fp, "%c", &ch);
		buffer[i] = ch;
		i++;
	}

	fclose(fp);

	printf("\nThe file contains :\n");
	printf("\n%s\n", buffer);

	printf("Writing to fifo 2 \n\n");

	f2 = open("myfifo", O_WRONLY);
	write(f2, buffer, strlen(buffer)+1);
	sleep(5);

	unlink("myfifo");




	return 0;
}
