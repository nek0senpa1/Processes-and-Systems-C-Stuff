#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_COMMANDLINE_LEN 8192
#define MAX_COMMANDLINE_ARGS 128
#define PATH_MAX 1024

/*  
Break up a command line into an array of char*s
ls -la 
becomes: 
exec_commands[0] == ls
exec_commands[1] == -la
exec_commands[2] == NULL <-- NULL terminator
*/

void parse_commandline(char *commandline, char *exec_commands[], int max_count)
{
    char *separators = " \r\n\t";
    char *token;
    char *str = commandline;
    int i = 0;

    // read individual tokens and store them in exec commands
    // while we have not reached the end of the commandline string, or the limit
    while (((token = strtok(str, separators)) != NULL && i < max_count))
    {
        str = NULL; // pass NULL for all subsequent calls to strtok
        exec_commands[i++] = token;
    }

    // this indicates there are no more commands
    exec_commands[i] = NULL;
}

int main(int argc, char *argv[])
{
    /*  
    a shell receives commandline args from users
    we need to parse those arguments
    shells need to print a prompt
    we should be able to exit with CTRL-D
    should be able to cd into specified directories
    we need to fork child processes to run files
    should be able to execute arbitrary files
    */

    char commandline[MAX_COMMANDLINE_LEN];
    // cd, ls etc.
    char *exec_commands[MAX_COMMANDLINE_ARGS];

    // while we have something in standard input
    while (printf(" $ "), fgets(commandline, sizeof commandline, stdin) != NULL)
    {
        // we need to parse the input
        // -1 for the NULL terminator
        parse_commandline(commandline, exec_commands, MAX_COMMANDLINE_ARGS - 1);

        // handle an empty command

        if (exec_commands[0] == NULL)
        {
            continue;
        }

        // handle built in commands

        // if they type exit or CTRL+D
        if (strcmp(exec_commands[0], "exit") == 0 || feof(stdin))
        {
            // exit
            exit(0);
        }
        else if (strcmp(exec_commands[0], "cd") == 0)
        {
            // chdir

            // check for correct usage
            if (exec_commands[1] == NULL)
            {
                if (chdir("/home") == -1)
                {
                    // this is an error with a built in function
                    // so we use perror
                    perror("chdir");
                };
            }
            if (exec_commands[2] != NULL)
            {
                // here, we make a custom error
                // so, we do fprintf to stderr
                fprintf(stderr, "Usage: cd dirname\n");
                continue;
            }

            if (chdir(exec_commands[1]) == -1)
            {
                perror("chdir");
            }

            continue;
        }

        // try to fork and exec the requested process
        pid_t pid = fork();

        if (pid == 0)
        {
            // execute the current command and any arguments along with it
            execvp(exec_commands[0], exec_commands);

            // if we get down here, there was an error
            perror("exec");
            exit(1);
        }
        else
        {
            // wait to clean up the child process
            wait(NULL);
        }
    }

    return 0;
}