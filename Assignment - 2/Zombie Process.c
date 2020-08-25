#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Current Process ID: %d\n",getpid());

    printf("Executing  FORK.\n");

    int pid = fork(); /* This will Create Child Process and
               Returns Child's PID */
    if(pid != 0)
    {
        /* Process Creation Failed ... */
      printf("After Forking, Process Control with Parent: %d\n\n", getpid());
    	printf("Parent Process now sleeping.\n\n");
    	sleep(10);
    	printf("\n\nProcess Control back with Parent.\n\n");
      printf("\n\nParent Process now in Zombie State.\n\n");
      while(1)
      {
          /*
              Infinite Loop that Keeps the
                 Process Running
          */

      }
      printf("Parent Process completed. Exiting.\n\n");
      exit(-1);
    }
    else  /* Child Process */
    {
  		printf("Conrtrol in Child Process.\n\n");
  		printf("\n\nChild's  ID : %d\n\n",getpid());
      printf("\n\nChild's Parent ID : %d\n\n",getppid());
  		printf("Child Process Completed and Exiting.\n\n");
  		exit(0);
     }
    return 0;
}
