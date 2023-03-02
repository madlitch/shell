Lab 2 Shell Project

Group 10

Lyba Mughees
100750490


Massimo Albanese
100616057


Daanyaal Tahir
100746644

Jean-Paul Saliba
100741759

Setup
----------------------------------------
- Open your Linux terminal and ensure you have C Installed. 
- To check if you have C installed, enter 'gcc --version'
- If C is not installed, first enter 'sudo apt update' and after enter 'sudo apt-get install gcc' than enter your credentials if you need to. 
- After ensuring that C is installed in your Linux virtual environment, see the "Launching myshell" section of this manual
<br><br>

Launching myshell
----------------------------------------
-Ensure myshell is launched in a Linux environment to get full functionality
1. Open the folder containing myshell.c in the Linux terminal
2. Check if you have make installed on Linux by using the 'make -version' command
3. If make is not installed on your Linux system first use the command 'sudo apt update' than use the command 'sudo apt install make' these commands will install make and allow you to run the makefile
4. Run the "make" command to execute the make file 
<br><br>

Launching myshell with a Batchfile 
----------------------------------------
- You can launch myshell and have it take input from a batchfile automatically 
- When launching myshell.c from your Linux terminal, include the name of the batchfile after myshell the format of the command is below 
- Format: 'sudo ./myshell <batchFile>'
- Note: ensure you have any empty line at the end of the batch file to prevent segmentation faults
- This command will allow myshell to execute the commands in the batchfile line by line


Commands
----------------------------------------

cd - changes the working directory<br>
clr -will clear all the contents on the screen<br>
dir - used to list the contents of the directory<br>
environ - list all the environment string<br>
echo - displays all content entered after the echo commamnd followed by a new line<br>
help - displays the user manual on to the terminal<br>
pause - pauses the operation of the shell until the Enter key is pressed<br>
quit - quit used to exit the shell<br>


Invocation of External Programs 
----------------------------------------
- Only the above commands are supported if you enter a command that does not exist you will get an error message. 
- Inputing anything other than the list of recognized commands will be interpreted as a program invocation of the external program named <programname>.
- After entering the program name, you can enter a list of arguments to pass to the external program.
- Format:	programname		OR	programname arg1 arg2 ... argn
<br><br>
	
I/O Redirection
----------------------------------------
Output Redirection using Truncate:
- Done using '>'.
	- '>' is used after a command, where all output to the terminal is redirected to a specified output file.
	- The output file will be overwritten if one already exists. It will create the file if it doesn't already exist.
	- Format:	command  outputDestination	OR	command parameter  outputDestination
