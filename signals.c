//обработка сигналов

// ctrl-C ctrl-D ctrl-\ should work like in bash.
// • When interactive:
// ◦ ctrl-C print a new prompt on a newline.
// ◦ ctrl-D exit the shell.
// ◦ ctrl-\ do nothing.

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


void myint()
{
	printf("нажал ctrl-c\n");
}




int main(int argc, char **argv, char **env)
{
	char	*str;

	str = readline("bash$ ");
	signal(SIGINT, myint);
	printf("|||%s|||\n", str);
}