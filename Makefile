<<<<<<< HEAD

   
=======
>>>>>>> e9f03b8ab1a7a59cdba981094d9be00a1343fb4c
NAME	=	minishell

HEAD	=	minishell.h

<<<<<<< HEAD
# CFLAGS	=	-Wall -Wextra -Werror
USER = vbackyet
CC		=	gcc

# SRCS	=	commands.c
SRCS	=	signals.c
OBJS 	= $(SRCS:%.c=%.o)
# @make -C ./libft 
# @$(CC) ./libft/libft.a -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -lreadline $(OBJS) -o $(NAME)

$(NAME): $(OBJS) $(HEAD)
	$(CC) -I ~/.brew/Cellar/readline/8.1.1/include -L ~/.brew/Cellar/readline/8.1.1/lib/  -lreadline $(OBJS) -o $(NAME)
=======
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
	@$(CC) ./libft/libft.a -lreadline $(OBJS) -o $(NAME)
>>>>>>> e9f03b8ab1a7a59cdba981094d9be00a1343fb4c

all: $(NAME)

clean:
<<<<<<< HEAD
	# @make -C ./libft clean
	@rm -f $(OBJS)

fclean: clean
	# @make -C ./libft fclean 
=======
	@make -C ./libft clean
	@rm -f $(OBJS)

fclean: clean
	@make -C ./libft fclean 
>>>>>>> e9f03b8ab1a7a59cdba981094d9be00a1343fb4c
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re