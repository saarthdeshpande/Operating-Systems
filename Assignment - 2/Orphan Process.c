#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid = getpid(), id = fork();
    if (id != 0)
    {
        printf("in parent process\t %d\n", getpid());
        sleep(5);
        printf("control with parent again\t %d\n", getpid());
        exit(-1);
    }
    // Note that pid is 0 in child process
    // and negative if fork() fails
    else
    {
        printf("in child process\t %d\t%d\n", getpid(), getppid());
        sleep(5);
        printf("control with child again\t %d\t%d\n", getpid(), getppid());
        sleep(5);
        printf("child now orphan\t%d\t%d\n", getpid(), getppid());
        exit(0);
    }

    return 0;
}
