NAME	=	minishell

HEAD	=	minishell.h

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

SRCS	=	minishell.c\
			commands.c\
			parsing/check_line.c\
			parsing/redirection.c\
			parsing/parsing.c\
			parsing/parse_utils.c

OBJS 	= $(SRCS:%.c=%.o)

$(NAME): $(OBJS) $(HEAD)
	@make -C ./libft bonus
	@$(CC) ./libft/libft.a -lreadline -L/Users/cliza/.brew/opt/readline/lib -I/Users/cliza/.brew/opt/readline/include $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@make -C ./libft clean
	@rm -f $(OBJS)

fclean: clean
	@make -C ./libft fclean 
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re