/*
Lab 2 - A simple Shell
Group 10
 */
#ifndef UTILITY_H_
#define UTILITY_H_

#define BUFFER_LEN 1024

// string tokenizer functions
extern int string_tokenizer(char* str, char tokens[][BUFFER_LEN]);

// returns current directory
extern void get_currentDir(char* pwd);

// changes the directory
extern void change_dir(char* pwd, char* path);

// clears the screen
extern void clear_screen(void);

// run executable
extern void run_exec(char *pwd, char *command);

// pauses the shell
extern void pause_shell(void);

// display help
extern void display_help(void);

// displays the directory
extern void display_dir(char* path);

// displays the environment variables
extern void display_environs(char env[][BUFFER_LEN]);

#endif /* UTILITY_H_ */