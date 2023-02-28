/*
Lab 2 - A simple Shell
Group 10
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "utility.h"
#include <fcntl.h>

// string tokenizer functions
extern int string_tokenizer(char *str, char tokens[][BUFFER_LEN]) {
    const char delimiter[2] = " ";
    int tokens_count = 0;
    char *token = strtok(str, delimiter);
    while (token != NULL) {
        strcpy(tokens[tokens_count], token);
        tokens_count++;
        token = strtok(NULL, delimiter);
    }
    return tokens_count;
}

// returns current directory
extern void get_currentDir(char *pwd) {
    getcwd(pwd, BUFFER_LEN);
}

// changes the directory
extern void change_dir(char *pwd, char *path) {
    int changed = chdir(path);
    if (strcmp(path, "") != 0) {
        if (changed == 0) {
            get_currentDir(pwd);
        } else {
            printf("%s> No such path exists!\n", pwd);
        }
    }
}

// clears the screen
extern void clear_screen(void) {
    system("cls||clear");
}

// run executable
extern void run_exec(char *pwd, char tokens[MAX_TOKENS][BUFFER_LEN], int token_count) {
    char pth[BUFFER_LEN] = {0};
    char args[BUFFER_LEN] = {0};
    int status;
    int flag_out;
    int flag_in;
    pid_t pid;

    // remove the dot
    memmove(tokens[0], tokens[0] + 1, strlen(tokens[0]));
    strcat(pth, pwd);
    strcat(pth, tokens[0]);

    for (int i = 1; i < token_count; i++) {
        // check for io redirect flags
        if (strcmp(tokens[i], "<") == 0) {
            flag_in = i + 1;
            i++;
            continue;
        } else if (strcmp(tokens[i], ">") == 0) {
            flag_out = i + 1;
            i++;
            continue;
        } else {
            strcat(args, " ");
            strcat(args, tokens[i]);
        }
    }

    if (access(pth, F_OK) == 0) {
        pid = fork();
        if (pid == 0) {
            // if stdout is redirected
            if (flag_out) {
                int fd = open(tokens[flag_out], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                // make stdout go to file
                dup2(fd, 1);
                close(fd);
            }

            execl(pth, args, NULL);
            // if exec fails, show error and kill child
            perror(": ");
            exit(0);
        }
        if (pid > 0) {
            // don't wait if '&' is the last token
            if (strcmp(tokens[token_count - 1], "&") != 0) {
                pid = wait(&status);
                printf("\nEnd of process %d: ", pid);
            }
            if (WIFEXITED(status)) {
                printf("\nThe process ended with exit(%d).\n", WEXITSTATUS(status));
            }
            if (WIFSIGNALED(status)) {
                printf("\nThe process ended with kill -%d.\n", WTERMSIG(status));
            }
        }
    } else {
        // if executable is not found
        perror(": ");
    }
}

// pauses the shell
extern void pause_shell(void) {
    printf("\n\nShell is now paused. Please press ENTER key to continue....\n\n");
    char code = (char) getchar();
    while (code != '\n') {
        code = (char) getchar();
    }
}

// displays help menu
extern void display_help(void) {
    printf("\nList of available commands:\n\n");
    printf("help\t\t\t Lists the help menu.\n");
    printf("dir <directory>\t\t Lists the contents of the directory\n");
    printf("environ\t\t\t Lists all the environment strings..\n");
    printf("echo <comment>\t\t Displays comment on the command line followed by a newline.\n");
    printf("cd <path>\t\t Changes the working directory to the specified path.\n");
    printf("clr\t\t\t Clears the screen.\n");
    printf("pause\t\t\t Pauses operation of the shell until the ENTER key is hit.\n");
    printf("quit\t\t\t Quits the shell.\n\n\n");
}

// displays the directory
extern void display_dir(char *path) {
    struct dirent *de;
    DIR *dr = NULL;
    if (strcmp(path, "") == 0) {
        dr = opendir(".");
    } else {
        dr = opendir(path);
    }
    if (dr == NULL) {
        printf("Could not find the directory specified!\n");
    }
    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
    }
    closedir(dr);
}

// displays the environment variables
extern void display_environs(char env[][BUFFER_LEN]) {
    printf("%s\n%s\n", env[0], env[1]);
}