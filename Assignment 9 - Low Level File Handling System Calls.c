#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>

int main()
{
	int n,fd, sz;
	char buff[50], c[100];	

	printf("\n# Enter text to write in the file:\n");
	n = read(0, buff, 50);

	// creating a new file using open.
	fd = open("file.txt",O_CREAT | O_RDWR, 0777);

	// O_RDONLY: read only, O_WRONLY: write only, O_RDWR: read and write, O_CREAT: create file if it doesn’t exist, O_EXCL: prevent creation if it already exists

	printf("\nWriting to the file and closing ...\n");
	write(fd, buff, n);
	int close(int fd);

  	fd = open("file.txt", O_RDONLY); 
	sz = read(fd, c, 100); 
	printf("\nCalling read function ...\n");
	printf("%d bytes were read.\n", sz); 
	c[sz] = '\0'; 
	printf("\nThose bytes are as follows: \n%s\n", c); 

	// closing the file
	int close(int fd);
	
	return 0;	
}