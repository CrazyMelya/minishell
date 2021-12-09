//обработка сигналов

// ctrl-C ctrl-D ctrl-\ should work like in bash.
// • When interactive:
// ◦ ctrl-C print a new prompt on a newline.
// ◦ ctrl-D exit the shell.
// ◦ ctrl-\ do nothing.


// надо установить homebrew
// https://github.com/daniiomir/faq_for_school_21#brew
// затем запустить
// brew install readline
// также нужно прописать в строках компиляции пути к библиотекам:
// https://21born2code.slack.com/archives/C0183HABMQQ/p1635870909122200?thread_ts=1635853265.120900&cid=C0183HABMQQ

#include "minishell.h"
#define STDERR 2



// void	ft_putstr_fd(char *s, int fd)
// {
// 	int	i;

// 	i = 0;
// 	if (s == NULL)
// 		return ;
// 	while (s[i] != '\0')
// 	{
// 		write(fd, &s[i], 1);
// 		i++;
// 	}
// }

// int ft_echo(char *str, int flag, int fd)
// {
// 	ft_putstr_fd(str, fd);
// 	if (flag)
// 		ft_putstr_fd("\n", fd);
// 	return(SUCCESS);
// }

// "/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)""





void	restore_prompt(int sig)
{
	// g_ret_number = 130;
	write(1, "\n", 1); // перенос на новую строку
	rl_replace_line("", 1);
	rl_on_new_line(); //сообщить процедурам обновления, что мы перешли на новую строку
	rl_redisplay(); //пишет строку bash
	(void)sig;
}

// void	ctrl_c(int sig)
// {
// 	g_ret_number = 130;
// 	write(1, "\n", 1);
// 	(void)sig;
// }

// void	back_slash(int sig)
// {
// 	g_ret_number = 131;
// 	printf("Quit (core dumped)\n");
// 	(void)sig;
// }
extern int rl_done;
void myint()
{
	// ft_putstr_fd("нажал ctrl-c   - новая строка\n", 2);
	// printf("нажал ctrl-c   - новая строка\n");
			// ft_putstr_fd("\b\b  ", STDERR);
		// ft_putstr_fd("\n", STDERR);
		// ft_putstr_fd("bash", STDERR);
		
		restore_prompt(0);
		rl_done = 0;
		// rl_on_new_line();
		// rl_redisplay();
		//  rl_replace_line();
		//  rl_redisplay();

}




void myint2()
{
	// printf("нажал backslash   - ничего не делает\n");
	// rl_replace_line("", "^");
	// rl_replace_line("", 33);
	rl_redisplay();
	// rl_on_new_line();
	// rl_redisplay();
}



void myint3()
{
	// printf("exit\n");
	exit(1);
}




// int main(int argc, char **argv, char **env)
// {

// 	char	*str;

// 	signal(2, myint);
// 	signal(3, myint2);
// 	rl_catch_signals = 0;
// 	while(1)
// 	{
// 	str = readline("bash$ ");
// 	// ft_echo( str, 0, 1);
// 	if (str == '\0')
// 		myint3();
// 	}
// 	// printf("|||%s|||\n", str);
// }

// gcc -I ~/.brew/Cellar/readline/8.1.1/include -L ~/.brew/Cellar/readline/8.1.1/lib/  -lreadline signals.c