MAKEFLAGS += --no-print-directory
NAME = minishell
CC = cc
CFLAGS = -Werror -Wextra -Wall -g
LDFLAGS = -lreadline
INCLUDES = -I INCLUDES
SRCS = src/main.c \
       src/parsing/parser.c \
       src/parsing/rendering.c \
       src/parsing/tokenization.c \
       src/parsing/trim_expand.c \
       src/parsing/valid.c


OBJS = $(SRCS:.c=.o)
	ECHO = echo -e
	RED = \033[0;31m
	GREEN = \033[0;32m
	RESET = \033[0m

all : $(NAME)
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)
	@$(ECHO) "$(GREEN) executable created $(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(ECHO) "$(RED) clean $(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(ECHO) "$(RED) fclean $(RESET)"

re: fclean all

.PHONY = all clean fclean re
