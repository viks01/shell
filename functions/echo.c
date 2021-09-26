#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "echo.h"

void echo(char **token_ptr) {

    // Print all tokens as they appear and just new line if entire command is 'echo'
    *token_ptr = strtok(NULL, " \t\n");
    while (*token_ptr != NULL) {
        printf("%s", *token_ptr);
        *token_ptr = strtok(NULL, " \t\n");
    }
    printf("\n");
}