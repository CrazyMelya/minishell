NAME	=	minishell

HEAD	=	minishell.h

#CFLAGS	=	-Wall -Wextra -Werror
USER	=	vbackyet
CC		=	gcc

# SRCS	=	commands.c

SRCS	=  	minishell.c \
			parsing/check_line.c\
			parsing/redirection.c\
			parsing/parsing.c\
			parsing/parse_utils.c\
			signals.c \
			commands.c \
			commands/ft_cd.c\
			commands/ft_echo.c\
			commands/ft_exit.c\
			commands/ft_export.c\
			commands/ft_pwd.c\
			commands/ft_env.c\
			commands/ft_unset.c
			
OBJS 	= $(SRCS:%.c=%.o)

$(NAME): $(OBJS) $(HEAD)
	@make -C ./libft bonus
	@$(CC) $(OBJS) -o $(NAME) -lreadline -L /Users/cliza/.brew/opt/readline/lib -I /Users/cliza/.brew/opt/readline/include ./libft/libft.a

all: $(NAME)

clean:
	@make -C ./libft clean
	@rm -f $(OBJS)

fclean: clean
	@make -C ./libft fclean 
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re


# $(CC) ./libft/libft.a -I ~/.brew/Cellar/readline/8.1.1/include -L ~/.brew/Cellar/readline/8.1.1/lib/  -lreadline $(OBJS) -o $(NAME)