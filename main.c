#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "ls.h"
#include "pinfo.h"
#include "syscommands.h"
#include "repeat.h"

int main(int argc, char *argv[]) {

    // Prompt display requirement
    char user[40], hostname[HOST_NAME_MAX + 1];
    char home_path[PATH_MAX];

    char *prompt = (char*) malloc(PATH_MAX + HOST_NAME_MAX + 45);
    prompt[0] = '<';
    prompt[1] = '\0';

    char *cwd = (char*) malloc(PATH_MAX);
    if (cwd == NULL) {
        printf("Memory full\n");
        return 1;
    }
    if (getcwd(cwd, PATH_MAX) == NULL) {
        perror("getcwd() error");
        return 1;
    } else {
        strcpy(home_path, cwd);
    }

    char *prwd = (char*) malloc(PATH_MAX);
    if (prwd == NULL) {
        printf("Memory full\n");
        return 1;
    }
    strcpy(prwd, home_path);

    getlogin_r(user, 40);
    strcat(prompt, user);
    strcat(prompt, "@");
    gethostname(hostname, HOST_NAME_MAX + 1);
    strcat(prompt, hostname);
    strcat(prompt, ":~>");

    // User input
    char input[101];   
    char *token;
    char *command;
    
    while (1) {
        printf("%s ", prompt);
        fgets(input, 100, stdin);

        // Tokenize for multiple commands
        char *copy = input;
        command = strtok_r(copy, ";\n", &copy);

        while (command != NULL) {
            // Tokenize to remove whitespace
            token = strtok(command, " \t\n");

            if (!token) {
                command = strtok_r(copy, ";\n", &copy);
                if (command == NULL) {
                    break;
                } else {
                    continue;
                }
            }

            // Compare first word of user input and call appropriate function
            if (strcmp(token, "pwd") == 0) {
                pwd(&cwd);
                token = strtok(NULL, " \t\n");
            } else if (strcmp(token, "echo") == 0) {
                echo(&token);
            } else if (strcmp(token, "cd") == 0) {
                token = strtok(NULL, " \t\n");
                cd(&token, &prompt, &cwd, &prwd, home_path);
            } else if (strcmp(token, "ls") == 0) {
                token = strtok(NULL, " \t\n");
                ls(&token, &cwd, home_path);
            } else if (strcmp(token, "pinfo") == 0) {
                token = strtok(NULL, " \t\n");
                pinfo(&token, &cwd);
            } else if (strcmp(token, "repeat") == 0) {
                token = strtok(NULL, " \t\n");
                repeat(&token, &prompt, &cwd, &prwd, home_path, input);
            } else if (strcmp(token, "exit") == 0) {
                goto end;
            } else {
                syscommands(&token, token);
            }
            
            command = strtok_r(copy, ";\n", &copy);
        }
    }

    // Fix memory leaks
end:
    free(prwd);
    free(cwd);
    free(prompt);
    
    return EXIT_SUCCESS;
}
