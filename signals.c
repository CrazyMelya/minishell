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
#include <sys/types.h>
#include <signal.h>

void myint()
{
	printf("нажал ctrl-c\n");
}

void myint2()
{
	printf("нажал backslash\n");
}





int main(int argc, char **argv, char **env)
{
	char	*str;

	signal(SIGINT, myint);
	signal(3, myint2);
	
	str = readline("bash$ ");
	
	printf("|||%s|||\n", str);
}