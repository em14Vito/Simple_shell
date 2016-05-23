# Simple_shell
Execute some simple shell command by C language

Manual:
1: Using makefile. it is easy to use this shell by using make command in terminal. also, you can clean things that you make before.  

2: when you start shell, you could enter most commands that OS shell supported like ls, mkdir, who, whoami, cp, mv, rm, rmdir, cal, chmod, pwd  

3: As for cd commands, the format should be like ‘cd ARG’. If there is no argument, it would put some error messages.  

4: History command would print all commands that have been executed before.  

5: exit & logout: these two commands are used to leaves the shell.
6: The shell could execute any other external programs as well. e.g, your run “./ hello” in the OS shell.
7:pipes - two (or more) commands can be connected together using the syntax COMMAND1 | COMMAND2. This connects the output of
COMMAND1 to the input of COMMAND2. (in my shell it only support one pipe)
8:redirection - standard input is redirected using < ARG. This means that command receives everything written in the file ARG, as it would be typed on the keyboard. Standard output is redirected by using > ARG.
