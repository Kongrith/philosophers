NAME	= philo

CXX		= cc -pthread
CFLAGS	= -Wextra -Wall -Werror

SRCS	= philo.c init.c parsing.c simulation.c thread_handler.c monitor.c utils.c
OBJS	= ${SRCS:.c=.o}

all: $(NAME)
	@echo "built $(NAME) successfully"

%.o: %.c
	$(CXX) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
