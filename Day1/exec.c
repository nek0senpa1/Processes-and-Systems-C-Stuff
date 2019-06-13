#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

/*  
the exec family of functions replaces the current process with the program named in the call
*/

int main(void)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        // negative pid denotes an error
        fprintf(stderr, "Error forking.");
        // exit with a non-zero exit code
        // this means something went wrong
        exit(1);
    }
    // when the child runs
    // we'll call the `ls` command
    if (pid == 0)
    {
        // call execlp
        // first argument is the relative path
        // second argument is the name of the program to transform into
        // last argument is just NULL to denote there are no more arguments
        execlp("ls", "ls", NULL);

        // if we get down here, exec failed
        // so, print an error
        perror("exec failed :(");
        exit(1);
    }
    else
    {
        // wait on the child
        wait(NULL);

        printf("Hi from the parent\n");
    }

    return 0;
}