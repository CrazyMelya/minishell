NAME	=	minishell

HEAD	=	minishell.h

# CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

SRCS	=  	minishell.c \
			free.c\
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
			commands/ft_unset.c\
			execute/env.c\
			execute/mini.c\
			execute/redirection.c\
			execute/utils.c\
			execute/utils_two.c\
			
OBJS 	= $(SRCS:%.c=%.o)

LIB 	= libft/libft.a

READLINE	= -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

%.o: %.c 
	@gcc $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(HEAD)
	@make -C ./libft bonus
	@$(CC) $(LIB) $(READLINE) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@make -C ./libft clean
	@rm -f $(OBJS)

fclean: clean
	@make -C ./libft fclean 
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
