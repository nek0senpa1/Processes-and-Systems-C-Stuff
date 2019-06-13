// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor
// returned by `fopen()`? What happens when they are written to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp = fopen("text.txt", "w");
    int rc = fork();
    // ------------------------------------------------ child process starts executing here
    if (rc < 0)
    { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    { // child process satisfies this branch

        char *child_statement = "here's the child\n";
        fwrite(child_statement, sizeof(char), strlen(child_statement), fp);
    }
    else
    {
        wait(NULL);

        char *parent_statement = "here's the parent\n";
        fwrite(parent_statement, sizeof(char), strlen(parent_statement), fp);
    }
    return 0;
}