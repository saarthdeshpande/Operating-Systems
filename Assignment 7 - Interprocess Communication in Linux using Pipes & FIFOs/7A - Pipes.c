#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define MAX 100

int main()
{
	int fd1[2],fd2[2],nbytes=1,a=0,c=1;
	pid_t pid;
	char file[MAX],readBuffer[MAX],re[MAX];
	char ch,ch1='\n';
	FILE *fp;
	
	pipe(fd1);
	pipe(fd2);
	
	pid=fork();

	if(pid==0)
	{ 
			close(fd1[0]);
			printf("     IN parent process \n");
			printf("     Enter the filename :");
			scanf("%s",file);	
			printf("     Filename is being sent by parent process \n");		
			write(fd1[1],file,(strlen(file)+1));
			close(fd1[1]);
			close(fd2[1]);
			sleep(3);
			
			
			printf("\n");
			printf("     File is being recieved by the parent and read\n");
			printf("     The file contents as recieved from child are\n");
			printf("\n");
			printf("     ");
			while(c!=0)
			{
			 c=read(fd2[0],&ch,sizeof(ch));
			 printf("%c",ch);
			}
			
			
			
					
			exit(0);
	  	
	  	
	}
	else
	{
	      printf("     Child is sleeping for some time\n");
		printf("\n");
		sleep(5);
	  	close(fd1[1]);
	  	printf("      In Child Process\n");
	  	read(fd1[0],readBuffer,sizeof(readBuffer));
	  	printf("\n    FILE %s is being read by the child process through pipe 1\n",readBuffer );
	  	fp=fopen(readBuffer,"r");
	  	close(fd1[0]);
	  	close(fd2[0]);
	  	printf("\n    Contents of '%s' are being sent to parent process through pipe 2    \n",readBuffer);
	  	printf("\n");
	  	
	  	while(a!=-1)
	  	{
	  		a=fscanf(fp,"%c",&ch);
	  		write(fd2[1],&ch,sizeof(ch));
	  	
	  	}
	  	close(fd2[1]);
	  	exit(0);
			
			
 	}
	
	
	return 0;
}
