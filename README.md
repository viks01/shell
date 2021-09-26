# Shell
*********************************************
## Descriptions of files 
### main.c
- Gets username and hostname to display the shell prompt, like in bash.
- Accepts input and tokenizes it by semicolons and whitespace.
- Calls built in as well as system functions and passes the tokens.
- Each valid command is executed by a separate function, defined in a separate file.
- Keeps track of the previous working directory (for cd implementation).

### echo.c
- Prints the rest of the input line (following the word 'echo') to the terminal (stdout stream), as it is, without spaces or tabs.
- Prints the tokens passed into it until NULL is encountered.

### pwd.c
- Sets the cwd (current working directory) string to the path name of the working directory.
- Prints the present working directory, considering the home directory to be the directory from which the shell is invoked.

### cd.c
- Accepts 1 argument as the target directory.
- Changes the current working directory to the argument, if possible.
- '-' flag changes to previous working directory while '~' flag (or no flag or argument) changes the directory to home directory. '.' flag signifies a change to the same directory (or no directory change) while '..' flag indicates a change into the parent directory.
- Changes shell prompt accordingly. If path of target directory is the home path or if the target directory is under the home directory, the home path is replaced by the '~' symbol in the shell prompt.

### ls.c
- Can accept '-l' and '-a' flags.
- Also accepts multiple arguments (directory/file paths)
- '-l' flag lists files in long listing format. If the listed files were last modified in a year other than the current year, the year will be specified in place of time (i.e., in place of 'hr:min').
- Displays files/directories one below the other.

### pinfo.c
- Displays process information like pid (process id), status of process, memory space, executable path for the process.
- Accesses files and directories under /proc folder to obtain process information.
- Checks if process is running in foreground or background.

### syscommands.c
- Executes other commands to run applications, spawn processes, etc. using execvp() function.
- Can run processes in foreground or background (add '&' at the end of command for background process).
- Prints process id and exit status of background process and uses fork() twice to implement this functionality.
- Dynamically allocates storage for tokens for the execvp() function.

### repeat.c
- Exeutes a command multiple times by calling the appropriate function.

### makefile
- Compiles all .c files using gcc with -Wall compile flag (gcc -Wall *.c).

## Error handling
- Error checks are coded into all files to handle different situations.
- Format checks for commands like cd and repeat have been implemented. 

***********************************************
## Compilation
- Makefile assumes all headers and .c files are in the same directory. 
- Run the command ```make``` to compile all .c files into the executable **a.out**.
