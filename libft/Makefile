NAME = libft.a
HEADER = I.
SRCS  = ft_putendl_fd.c \
    ft_putnbr_fd.c \
    ft_putstr_fd.c \
    ft_putchar_fd.c \
    ft_strmapi.c \
    ft_itoa.c \
    ft_split.c \
    ft_strtrim.c \
    ft_strjoin.c \
    ft_substr.c \
    ft_strdup.c \
    ft_calloc.c \
    ft_tolower.c \
    ft_atoi.c \
    ft_isascii.c \
    ft_memset.c \
    ft_bzero.c \
    ft_memmove.c \
    ft_memccpy.c \
    ft_memcpy.c \
    ft_memchr.c \
    ft_strlen.c \
    ft_strlcpy.c \
    ft_strlcat.c \
    ft_strncmp.c \
    ft_strnstr.c \
    ft_isalnum.c \
    ft_isalpha.c \
    ft_isdigit.c \
    ft_isprint.c \
    ft_memcmp.c \
    ft_strchr.c \
    ft_strrchr.c \
    ft_toupper.c \
    ft_toupper.c \


OBJS  = $(SRCS:.c=.o)
CC   = gcc
CFLAGS  =  -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS) $?
	ranlib $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -o $@ -I.

clean:
	rm -rf $(OBJS)

fclean:  clean
	rm -rf $(NAME)
   
re:	fclean all