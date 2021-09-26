#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include "pinfo.h"

void pinfo(char **token_ptr, char **cwd_ptr) {

    pid_t pid;
    char pid_str[10];
    char *status;
    char *mem;
    char path[PATH_MAX], temp[PATH_MAX];
    
    // Obtain effective pid and executable path
    if (*token_ptr == NULL) {
        pid = getpid();
        strcpy(path, "~/a.out");                    
    } else {
        pid = atoi(*token_ptr);
        sprintf(temp, "/proc/%d/exe", pid);
        readlink(temp, path, PATH_MAX);
    }
    sprintf(pid_str, "%d", pid);
    
    // Memory and process status
    char process_file[100];
    char line[201];

    sprintf(process_file, "/proc/%d/statm", pid);
    FILE *fp = fopen(process_file, "r");
    fgets(line, 200, fp);
    mem = strtok(line, " ");
    fclose(fp);

    char line2[PATH_MAX];
    sprintf(process_file, "/proc/%d/stat", pid);
    fp = fopen(process_file, "r");
    fgets(line2, 200, fp);
    status = strtok(line2, " ");
    for (int i = 0; i < 2; i++) {
        status = strtok(NULL, " ");
    } 
    fclose(fp);

    // Check if process is running in foreground or background
    int fd = open("/dev/tty", O_RDONLY);
    int check = 0;
    if (getpgrp() == tcgetpgrp(fd)) {
        check = 1;
    }
    close(fd);

    // Print process information
    printf("pid -- %d\n", pid);
    printf("Process Status -- %s", status);
    if (check) {
        putchar('+');
    } 
    putchar('\n');    
    printf("memory -- %s kB {Virtual Memory}\n", mem);
    printf("Executable Path -- %s\n", path);
}
