#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

#include "syscommands.h"

int syscommands(char **token_ptr, char *prog_name) {

    // Store tokens in an array of strings for execvp()
    char *tokens[20];
    char *temp = *token_ptr;
    int i = 0;
    tokens[i] = strdup(prog_name);                  // Uses heap memory for dynamic allocation
    i++;
    *token_ptr = strtok(NULL, " \t\n");
    while (*token_ptr != NULL) {
        tokens[i] = strdup(*token_ptr);
        *token_ptr = strtok(NULL, " \t\n");
        i++;
    }
    tokens[i] = NULL;                               // Last parameter needs to be NULL for execvp()
    *token_ptr = temp;

    // Differentiate between background and foreground process
    if (strcmp(tokens[i-1], "&") == 0) {            // Background process 
        free(tokens[i-1]);
        tokens[i-1] = NULL;

        int forkReturn = fork();
        if (forkReturn == 0) {                      // Child process
            pid_t container = fork();
            if (container == 0) {                   // Child process
                if (execvp(tokens[0], tokens) == -1) {
                    i = 0;
                    while (tokens[i] != NULL) {
                        free(tokens[i]);
                        i++;
                    }
                    printf("ERROR: %s\n", strerror(errno));
                    exit(1);
                }
            } else {                                // Parent process
                printf("%d\n", container);
                int status;
                waitpid(-1, &status, 0);
                fprintf(stderr, "\n%s with pid %d exited ", temp, container);
                if (status == 0)
                    fputs("normally", stderr);
                else
                    fputs("abnormally", stderr);

                i = 0;
                while (tokens[i] != NULL) {
                    free(tokens[i]);
                    i++;
                }
                exit(0);
            }
        } else {                                    // Parent process
            sleep(1);
            i = 0;
            while (tokens[i] != NULL) {
                free(tokens[i]);
                i++;
            }
        }
    } else {                                        // Foreground process
        int forkReturn = fork();
        if (forkReturn == 0) {                      // Child process
            if (execvp(tokens[0], tokens) == -1) {
                printf("ERROR: %s\n", strerror(errno));
                i = 0;
                while (tokens[i] != NULL) {
                    free(tokens[i]);
                    i++;
                }
                exit(1);
            }
        } else {                                    // Parent process
            wait(NULL);
            i = 0;
            while (tokens[i] != NULL) {
                free(tokens[i]);
                i++;
            }
        }
    }

    return 0;
}
