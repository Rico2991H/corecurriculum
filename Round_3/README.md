*This project has been created as part of the 42 curriculum by [dmungunt,rhoogend].*

**DESCRIPTION**
This documents gives a brief overview of the minishell made as part of the 42 coding school curriculum. For this project we wrote a shell that mimics "to the extent of our project requirements", the behaviour of the bash SHELL. Some of these requirements are:
- handling redirections
- conntecting the outputs and input of various commands using pipes
- handling environment variables
- handling $? expansion
- handling the signals ctrl-C ctrl-D ctrl-\
- handling system commands and the following built-in commands:
	◦ echo with option -n
	◦ cd with only a relative or absolute path
	◦ pwd with no options
	◦ export with no options
	◦ unset with no options
	◦ env with no options or arguments
	◦ exit with no options

for this project we decided to include the bonus requirements which are:
- handling && and || with parentheses for priorities
- handling * wildcards for the current working drectory

**INSTRUCTIONS**
1. Making an executable
You can make an executable by calling make, this will create all necessary object files and the executable, by calling make clean you delete the object files and keep the executable, make fclean deletes the object files and the executable. By using make re you redo the creation of the object files and executable. The Makefile includes a piece of script that surpresses all readline memory leak erros. 

2. Starting the minishell
To start the minishell you use the terminal and execute the program by typing ./minishell and pressing enter.

3. Using the minishell
After you start the minishell will prompt you to type in a command, the command can then be executed by pressing enter.
- The minishell will allow you to execute various commands as described above by typing in the name and the required argument.
- The minishell will allow you to execute multiple command by using && (and) and || (or) operators.
- The minishell will allow you to connext various commands by using (|)pipes.
- The minishell will allow you to prioritize part of a command line by using ("()")parentheses.
- The minishell will allow you to assign variables by using *name=value* or by using export *name=value*.
- The minishell will allow you to redirect input and output using <,>,<< or >>.
- The minishell will allow you to use wildcards for the current working directory by typing part of the filename and using  * as a placeholder for the rest of the filename.
- The minishell will allow you to use the following signals:
	◦ ctrl-C displays a new prompt on a new line.
	◦ ctrl-D exits the shell.
	◦ ctrl-\ does nothing.
- In case of invalid commands the minishell will provide you with a descriptive error message.

4. Closing the minishell
The minishell can be closed by using the signal ctrl-D or by typing exit. 

**RESOURCES**
https://www.youtube.com/watch?v=224plb3bCog
https://www.youtube.com/watch?v=bxpc9Pp5pZM&t=601s
https://www.youtube.com/watch?v=OIKL6wFjFOo
https://copyconstruct.medium.com/bash-redirection-fun-with-descriptors-e799ec5a3c16
https://dev.to/sameerkatija/github-markdown-cheat-sheet-everything-you-need-to-know-to-write-readme-md-2eca
https://chatgpt.com
https://claude.ai/new
https:stackoverlow.com
https://www.geeksforgeeks.org/linux-unix/piping-in-unix-or-linux/
geeksforgeeks.org/compiler-design/introduction-of-parsing-ambiguity-and-parsers-set-1/
https://www.youtube.com/watch?v=ENKT0Z3gldE

**Usage of AI**
AI was applied in various ways for this project, for example chatgpt.com and claude.ai were used to acquire knowledge about various new concepts such as tokenization or parsing and an explanation of newly introduced functions that we were allowed to use for this project. AI is also used as a sparrings partner, we would come up with ideas and check with an AI agent whether it was viable. Or we would come up with ideas and compare it with the approach that was applied for the bash shell. Furthermore AI has been used for debugging and code suggestions at times where we felt we were really stuck. It is important to note that the usage of AI requires critical reviews and the mental fitness and knowledge to challenge the AI's suggestions, as the line of code increase AI's reliability for doing good suggestions decreases. We have learned that the usage of AI, is as powerfull as it is risky for young developers. wrong suggestions can easily send you in a complete wrong direction, and with a lack of understanding of the matter, there is a risk of copy pasting segments of code that break your software completely. furthermore it can be tempting to overuse AI when the brain has already put in a lot of hours of work. But it it a nice feeling that our capacity as programmers to question the AI's suggestions is developing as well.  

