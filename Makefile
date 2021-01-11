CC = gcc
CFLAGS = -Wall -Wextra -Werror
ARFLAGS = rcs
SRCS = ft_printf.c hex.c int.c percent.c string.c utilsnother.c
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	ar $(ARFLAGS) $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
