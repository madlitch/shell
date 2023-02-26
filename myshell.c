/*
Lab 2 - A simple Shell
Group 10
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 1024
#define MAX_TOKENS 10

int main(int argc, char *argv[]) {
    // Input buffer and and commands
    char environ[2][BUFFER_LEN] = {0};
    char pwd[BUFFER_LEN] = {0};
    char shell[BUFFER_LEN] = {0};
    char buffer[BUFFER_LEN] = {0};
    char command[BUFFER_LEN] = {0};
    char tokens[MAX_TOKENS][BUFFER_LEN] = {0};
    int token_count = 0;

    FILE *fd;

    // Check to see if user has provided a batchfile
    if (argc > 1) {
        // If batchfile, then open the file for reading
        fd = fopen(argv[1], "r");
        if (fd == NULL) {
            perror("There was an error opening the specified file");
            exit(1);
        }
    } else {
        fd = stdin;
    }

    printf("\n*************************************************************\n\n");
    printf("\n                 **** Welcome to myshell ****                  \n");
    printf("\n*************************************************************\n\n\n\n");
    get_currentDir(pwd);
    get_currentDir(shell);

    strcat(environ[0], pwd);
    strcat(environ[1], shell);

    printf("%s> ", pwd);

    // Continuously loop to get user input from terminal or file
    // and end loop when end of fille or shell is exited
    while (fgets(buffer, BUFFER_LEN, fd) != NULL) {
        // Perform string tokenization to get the command and argument
        int index = 0;
        while (buffer[index] != '\n') {
            index++;
        }
        buffer[index] = '\0';

        token_count = string_tokenizer(buffer, tokens);
        strcpy(command, tokens[0]);

        // 'cd' command for changing directory.
        if (strcmp(command, "cd") == 0) {
            change_dir(pwd, tokens[1]); // update the pwd
            strcat(environ[0], pwd);
        }

            // 'clr' command for clearing the screen.
        else if (strcmp(command, "clr") == 0) {
            clear_screen();
        }

            // 'dir' command to list the contents of directory
        else if (strcmp(command, "dir") == 0) {
            display_dir(tokens[1]);
            printf("\n");
        }

            // 'environ' command to list the environment variables
        else if (strcmp(command, "environ") == 0) {
            display_environs(environ);
        }

            // 'echo' command to display a comment
        else if (strcmp(command, "echo") == 0) {
            printf("%s> ", pwd);
            for (int i = 1; i < token_count; i++) {
                printf("%s ", tokens[i]);
            }
            printf("\n");
        }

            // 'help' command to display the user manual
        else if (strcmp(command, "help") == 0) {
            display_help();
        }

            // 'pause' command to pause the operation of the shell
        else if (strcmp(command, "pause") == 0) {
            pause_shell();
        }

            // run exec
        else if (command[0] == *".") {
            run_exec(pwd, command);
        }

            // lists the contents of the specified directory
        else if (strcmp(command, "dir") == 0) {
            display_dir(tokens[1]);
            printf("\n");
        }

            // run the echo command
        else if (strcmp(command, "echo") == 0) {
            printf("%s> ", pwd);
            for (int i = 1; i < token_count; i++) {
                printf("%s ", tokens[i]);
            }
            printf("\n");
        }

            // display environment variables
        else if (strcmp(command, "environ") == 0) {
            display_environs(environ);
        }

            // 'quit' command to quit the shell
        else if (strcmp(tokens[0], "quit") == 0 || strcmp(tokens[0], "exit") == 0) {
            return EXIT_SUCCESS;
        }

            // Unsupported command
        else {
            printf("%s> ", pwd);
            printf("Unsupported command, use help to display the manual\n");
        }

        // clear the buffer, command and token variables
        memset(buffer, 0, sizeof buffer);
        memset(command, 0, sizeof command);
        for (int i = 0; i < MAX_TOKENS; i++) {
            memset(tokens[i], 0, sizeof tokens[i]);
        }

        // print the present working directory
        printf("%s> ", pwd);
    }
    return EXIT_SUCCESS;
}
