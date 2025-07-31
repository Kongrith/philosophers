NAME		= philo

CXX			= cc
CFLAGS	= -Wextra -Wall -Werror -pthread
# CFLAGS		= -g -Wall -Werror -Wextra -O3 -fsanitize=address
LINK_CFLAGS = $(CFLAGS)


SRCS	=	philo.c \
			init.c \
			parsing.c \
			simulation.c \
			monitor.c \
			thread_handler.c \
			thread_handler_utils.c \
			utils.c \
			clean.c
			
OBJS	= ${SRCS:.c=.o}

all: $(NAME)
	@echo "built $(NAME) successfully"

%.o: %.c
	$(CXX) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(LINK_CFLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
