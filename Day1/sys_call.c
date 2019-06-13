#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    /*  
    fork makes a new process that starts running the moment fork returns
    returns twice: once for the parent and once for the child
    the return values are different for the parent and child
    the pid is 0 for the child
    the pid is negative for errors
    process tree is like a family tree
    child processes can access all the variables from the parent, but they can't modify them
    */
    pid_t pid = fork();

    if (pid < 0)
    {
        // negative pid denotes an error
        fprintf(stderr, "Error forking.");
        // exit with a non-zero exit code
        // this means something went wrong
        exit(1);
    }
    if (pid == 0)
    {
        printf("Hello world from the child\n");
    }
    else
    {
        // you want to have a wait call for every fork
        // the parent waits for the child to terminate before running
        // this will guarantee that the child runs first
        wait(NULL);
        printf("Hello world from the parent\n");
    }

    return 0;
}