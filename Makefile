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
       src/parsing/valid.c \
	   src/lib/isalnum.c \
	   src/lib/memcpy.c \
	   src/lib/realloc.c \
	   src/lib/split.c \
	   src/lib/strchr.c \
	   src/lib/strdup.c \
	   src/lib/strjoin.c \
	   src/lib/strncmp.c \
	   src/lib/strncpy.c \
	   src/lib/strrchr.c \
	   src/lib/strtrim.c \
	   src/lib/substr.c \
	   src/lib/split_env.c \
	   src/built-in/echo.c \
	   src/built-in/ft_cd.c \
	   src/built-in/ft_export.c \
	   src/built-in/ft_pwd.c \
	   src/built-in/unset.c \
	   src/built-in/ft_env.c \
	   src/exec/execute_ast.c \
	   src/env/create_env.c \
	   src/env/env_utils.c \
	   src/ft_free/ft_free.c


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
