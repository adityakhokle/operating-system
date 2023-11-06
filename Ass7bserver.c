/*
Assignment No. 7:
Inter process communication in Linux using following.
B. Inter-process Communication using Shared Memory using System V. Application to demonstrate:
Client and Server Programs in which server process creates a shared memory segment and writes the
message to the shared memory segment. Client process reads the message from the shared memory
segment and displays it to the screen.
*/

//Server

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSIZE 27 // Define a constant for the maximum size of the shared memory segment

void die(char *s) {
    perror(s); // Function to display an error message and exit the program
    exit(1);
}

int main() {
    int shmid, retval; // Declare 'retval' here to store return values
    key_t key;
    char *shm, *s; // Declare pointers to shared memory and a character pointer

    key = 5678; // Define a key for the shared memory segment

    // Create or access the shared memory segment with key '5678' and size 'MAXSIZE' (IPC_CREAT specifies to create if it doesn't exist, 0666 specifies permissions)
    if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
        die("shmget");

    // Attach to the shared memory segment and get a pointer to it
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
        die("shmat");

    printf("Enter a string (up to 26 characters): ");
    if (fgets(shm, MAXSIZE, stdin) == NULL) {
        printf("Input error\n");
        exit(1); // Handle input error
    }

    /*
     * Wait until the other process
     * changes the first character of our memory
     * to '*', indicating that it has read what
     * we put there.
     */
    while (*shm != '*') {
        sleep(1); // Sleep for 1 second and check if the first character of shared memory is '*'
    }
    retval = shmdt(shm); // Detach from the shared memory segment
    if (retval < 0) {
        printf("detachment failure");
        return 0; // Handle detachment failure
    }

    exit(0); // Exit the program
}
