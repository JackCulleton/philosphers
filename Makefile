NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c validate.c validate_alloc.c validate_checks.c init_thread.c \
	monitor.c routine.c todo.c forks.c actions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all
