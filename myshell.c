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

#define MAXIMUM_TOKENS 10
#define BUFFER_LENGTH 1024

int main(int argc, char *argv[])
{
    // Initialize the variables
	char environ[2][BUFFER_LENGTH], pwd[BUFFER_LENGTH], shell[BUFFER_LENGTH], buffer[BUFFER_LENGTH], command[BUFFER_LENGTH], tokens[MAXIMUM_TOKENS][BUFFER_LENGTH] = {0};
	int token_count = 0;
	FILE* fd; // Declare fd for batchfile

	// Check to see if user has provided a batchfile
    if (argc > 1){
		// If batchfile, then open the file for reading
		fd = fopen(argv[1],"r");
		if (fd == NULL){
			perror("There was an error opening the specified file");
			exit(1);
		}
	}
	else {
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
    while (fgets(buffer, BUFFER_LENGTH, fd) != NULL){
        // Perform string tokenization to get the command and argument
	    int index = 0;
		while (buffer[index] != '\n'){
			index++;
		}
		buffer[index] = '\0';
		
		token_count = string_tokenizer(buffer, tokens);
		strcpy(command, tokens[0]);
		
        // 'cd' command for changing diretory. 
        if (strcmp(command, "cd") == 0){
			change_dir(pwd, tokens[1]); // update the pwd
			strcat(environ[0], pwd);
        }
		
		// 'clr' command for clearing the screen. 
		else if (strcmp(command, "clr") == 0){
			clear_screen();
		}

		// 'dir' command to list the contens of directory
		else if (strcmp(command, "dir") == 0){
			display_dir(tokens[1]);
			printf("\n");
		}

		// 'environ' command to list the environment variables
		else if (strcmp(command, "environ") == 0){
			display_environs(environ);
		}

		// 'echo' command to display a comment
		else if (strcmp(command, "echo") == 0){
			printf("%s> ", pwd);
			for (int i = 1; i < token_count; i++){
				printf("%s ", tokens[i]);
			}
			printf("\n");
		}

		// 'help' command to display the user manual
		else if (strcmp(command, "help") == 0){
			 display_help();
		}	
		
		// 'pause' command to pause the operation of the shell
		else if (strcmp(command, "pause") == 0){
			pause_shell();
		}	
		
        // 'quit' command to quit the shell
        else if (strcmp(tokens[0], "quit") == 0){
            printf("Bye!\n");
			exit(0);
        }

        // Unsupported command
        else{
			printf("%s> ", pwd);
            printf("Unsupported command, use help to display the manual\n");
        }
		
		// clear the buffer, command and token variables
		memset(buffer, 0, sizeof buffer);
		memset(command, 0, sizeof command);
		for (int i = 0; i < MAXIMUM_TOKENS; i++){
			memset(tokens[i], 0, sizeof tokens[i]);
		}
		
		// print the present working directory
		printf("%s> ", pwd);
    }
    exit(0);
}
