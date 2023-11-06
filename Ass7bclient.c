/*
Assignment No. 7:
Inter process communication in Linux using following.
B. Inter-process Communication using Shared Memory using System V. Application to demonstrate:
Client and Server Programs in which server process creates a shared memory segment and writes the
message to the shared memory segment. Client process reads the message from the shared memory
segment and displays it to the screen.
*/

//Client

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

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

    // Create or access the shared memory segment with key '5678' and size 'MAXSIZE' (0666 specifies permissions)
    if ((shmid = shmget(key, MAXSIZE, 0666)) < 0)
        die("shmget");

    // Attach to the shared memory segment and get a pointer to it
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
        die("shmat");

    // Now read what the server put in the memory.
    for (s = shm; *s != '\0'; s++) {
        putchar(*s); // Print the characters stored in the shared memory segment
    }
    putchar('\n'); // Print a newline character

    /*
     * Change the first character of the
     * segment to '*', indicating that the segment has been read.
     */
    
    *shm = '*'; // Change the first character of the shared memory segment to '*'
    retval = shmdt(shm); // Detach from the shared memory segment
    if (retval < 0) {
        printf("detachment failure");
        return 0; // Handle detachment failure
    }
    retval = shmctl(shmid, IPC_RMID, NULL); // Remove the shared memory segment
    // The 'shmctl' function with 'IPC_RMID' removes the shared memory segment entirely

    exit(0); // Exit the program
}
