#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define TEXT_SZ 2048
// Alternatively, BUFSIZ can also be used

// BUFSIZ value depends on preprocessor (below code from stdio.h)
/*
  #if defined(_M_MPPC)
  #define BUFSIZ 4096
  #else \/* defined (_M_MPPC) *\/
  #define BUFSIZ 512
  #endif \/* defined (_M_MPPC) *\/
 */

struct shared_use_st {
    int written_by_you;
    char some_text[TEXT_SZ];
};

int main()
{
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    char buffer[BUFSIZ];
    int shmid;
    // Allocate shared memory
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    // IPC_CREAT has the value of 512 in decimal (depends on system)
    // 0666 sets the access permissions of the memory segment
    // IPC_CREAT tells the system to create a new memory segment for the shared memory
    // Give program access to shared memory
    shared_memory = shmat(shmid, (void *)0, 0);
    printf("Memory attached at %X\n", (int)shared_memory);

    shared_stuff = (struct shared_use_st *)shared_memory;
    while(running) {
        while(shared_stuff -> written_by_you == 1) {
        // sleep(1);
        // printf("waiting for server...\n");
            continue;
        }
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        strncpy(shared_stuff -> some_text, buffer, TEXT_SZ);
        shared_stuff -> written_by_you = 1;
        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
    }
    // Detach shared memory
    shmdt(shared_memory);
    // Delete Shared memory
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
