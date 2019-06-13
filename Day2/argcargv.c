#include <stdio.h>

int main(int argc, char *argv[])
{
    // number of command line arguments
    printf("%d\n", argc);
    // each command line argument

    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}