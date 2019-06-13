#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char command[1024] = "python3 choice.py";
    char output[1024];

    for (int i = 1; i < argc; i++)
    {
        // add each command line argument to the string
        sprintf(command, "%s %s", command, argv[i]);
    }

    // open the python file with a pipe
    fp = popen(command, "r"); // open the python file for reading
    pid_t pid = fork();

    // if we're at the child
    if (pid == 0)
    {
        while (fgets(output, sizeof(output), fp) != NULL)
        {
            printf("The winner is... %s", output); // Read the output from the python file
        }
    }
    else
    {
        // wait on the child so we don't get a zombie process
        wait(NULL);
    }

    pclose(fp);

    return 0;
}