#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    // using wait with an *int allows the parent to get the exit status of the child process
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
        printf("Let's wait\n");
        exit(7);
    }
    else
    {
        int status;
        wait(&status);

        // this checks if the child exited normally
        if (WIFEXITED(status))
        {
            // WEXITSTATUS gives us the actual status
            printf("parent: child exited with status %d\n", WEXITSTATUS(status));
        }
    }
}