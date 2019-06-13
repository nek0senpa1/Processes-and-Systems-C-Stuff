#include <stdio.h>
#include <string.h>
#include <stdlib.h> // <-- include this for free and malloc

/*  
We have an API, and when there's an error we want to send a message to the client.
The message has 3 components
Error code - 400/404/500
Error name - Not Found/Bad Request/Internal Server Erro
Error Message - The house is on fire
*/

struct HttpError_t
{
    int error_code;
    char *error_name;
    char *error_message;
};
// this is so we don't have to repeat struct every time
typedef struct HttpError_t HttpError;

HttpError *create_error(int error_code, char *error_name, char *error_message)
{
    // mallocate our struct
    HttpError *error = malloc(sizeof(HttpError));
    // mallocate each string
    // you have to allocate the length + 1
    // because of the null terminating value
    // then use strcpy to assign the arguments to the strings

    error->error_name = malloc(strlen(error_name) + 1);
    strcpy(error->error_name, error_name);

    error->error_message = malloc(strlen(error_message) + 1);
    strcpy(error->error_message, error_message);

    error->error_code = error_code;

    return error;
}

void free_error(HttpError *error)
{
    // free all mallocated properties
    free(error->error_name);
    free(error->error_message);

    // free the struct itself
    free(error);
}

HttpError *create_internal_server_error(void)
{
    return create_error(500, "Internal Server error", "Oops, something went wrong!");
}

int main(void)
{
    HttpError *error = create_internal_server_error();

    printf("%d - %s\n", error->error_code, error->error_name);
    printf("%s\n", error->error_message);

    free_error(error);
    return 0;
}