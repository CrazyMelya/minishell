NAME	=	minishell

HEAD	=	minishell.h

# CFLAGS	=	-Wall -Wextra -Werror
USER = vbackyet
CC		=	gcc

# SRCS	=	commands.c
SRCS	=	signals.c\
			minishell.c\
			commands.c\
			parsing/check_line.c\
			parsing/redirection.c\
			parsing/parsing.c\
			parsing/parse_utils.c\
			commands/ft_cd.c\
			commands/ft_echo.c\
			commands/ft_exit.c\
			commands/ft_export.c\
			commands/ft_pwd.c\
			commands/ft_unset.c
OBJS 	= $(SRCS:%.c=%.o)
# @make -C ./libft 
# @$(CC) ./libft/libft.a -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -lreadline $(OBJS) -o $(NAME)

$(NAME): $(OBJS) $(HEAD)
	$(CC) -I ~/.brew/Cellar/readline/8.1.1/include -L ~/.brew/Cellar/readline/8.1.1/lib/ ./libft/libft.a  -lreadline $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@make -C ./libft clean
	@rm -f $(OBJS)

fclean: clean
	@make -C ./libft fclean 
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re