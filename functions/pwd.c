#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

#include "pwd.h"

void pwd(char **cwd_ptr) {

    // Set cwd to the present working directory
    if (getcwd(*cwd_ptr, PATH_MAX) == NULL) {
        perror("getcwd() error");
    }
    else {
        printf("%s\n", *cwd_ptr);
    }
}
