NAME = philo

SRCS = philo.c

HEADER = ./includes/philo.h

OBJS = $(SRCS:.c=.o)

CC = clang -g3 -fsanitize=address
#CC = clang -g3 -fsanitize=thread

CFLAGS = -Wall -Wextra -Werror -pthread 

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

