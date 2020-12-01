#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define MAX 100

int main() {
	int fd1[2], fd2[2], a = 0, c = 1;
	pid_t pid;
	char file[MAX],readBuffer[MAX];
	char ch = '\n';
	FILE *fp;
	
	pipe(fd1);
	pipe(fd2);
	
	pid = fork();

	if(pid == 0) {
			close(fd1[0]);      // close read end of pipe 1
			printf("\tIN parent process \n");
			printf("\tEnter the filename :");
			scanf("%s",file);	
			printf("\tFilename is being sent by parent process\n");
			write(fd1[1],file,(strlen(file)+1));    // write from file to pipe 1 using write end of pipe
			close(fd1[1]);   // close write end of pipe 1
			close(fd2[1]);   // close write end of pipe 2
			sleep(3);
			
			
			printf("\n");
			printf("\tFile is being received by the parent and read\n");
			printf("\tThe file contents as received from child are\n");
			printf("\n");
			printf("\t");
			while(c != 0) {
                 c = read(fd2[0],&ch,sizeof(ch));   // read character-wise from pipe 2 via its read end and print to screen
                 printf("%c",ch);
			}
			exit(0);
	} else {
        printf("\tChild is sleeping for some time\n");
		printf("\n");
		sleep(5);
	  	close(fd1[1]);  // close write end of pipe 1
	  	printf("\tIn Child Process\n");
	  	read(fd1[0],readBuffer,sizeof(readBuffer)); // read from pipe 1 via its read end to buffer
	  	printf("\n\tFILE %s is being read by the child process through pipe 1\n",readBuffer);
	  	fp = fopen(readBuffer,"r");
	  	close(fd1[0]);   // close read end of pipe 1
	  	close(fd2[0]);   // close read end of pipe 1
	  	printf("\n\tContents of '%s' are being sent to parent process through pipe 2\t\n",readBuffer);
	  	printf("\n");
	  	
	  	while(a != -1) {    // write each character from buffer to pipe 2 via its write end
	  		a = fscanf(fp,"%c",&ch);
	  		write(fd2[1],&ch,sizeof(ch));
	  	}
	  	close(fd2[1]);  // close write end of pipe 1
	  	exit(0);
 	}
}
