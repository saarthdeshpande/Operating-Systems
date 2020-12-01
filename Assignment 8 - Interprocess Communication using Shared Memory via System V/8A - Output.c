#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>


struct my_msg_st {
	long int my_msg_type;
	char some_text[BUFSIZ];
};

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	long int msg_to_receive = 0;
	
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

	// IPC_CREAT has the value of 512 in decimal (depends on system)
	// 0666 sets the access permissions of the memory segment
	// IPC_CREAT tells the system to create a new memory segment for the shared memory

	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	while(running) {
		if (msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_receive, 0) == -1) {   // if messages are not retrieved from queue
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		// BUFSIZ value depends on preprocessor (below code from stdio.h)
		/*
		  #if defined(_M_MPPC)
		  #define BUFSIZ 4096
		  #else \/* defined (_M_MPPC) *\/
		  #define BUFSIZ 512
          #endif \/* defined (_M_MPPC) *\/
		 */

		printf("You wrote: %s", some_data.some_text);
		if (strncmp(some_data.some_text, "end", 3) == 0)    // compare at most first n(3) bytes of string 1 and 2
			running = 0;
	}

	if (msgctl(msgid, IPC_RMID, 0) == -1)  {    // if failed to destroy message queue
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}