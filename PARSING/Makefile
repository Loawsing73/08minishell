MAKEFLAGS += --no-print-directory
NAME = parser
CC = cc
CFLAGS = -Werror -Wextra -Wall -g
LDFLAGS = -lreadline
INCLUDES = -I INCLUDES
SRCS = SRCS/parser.c \
	   SRCS/rendering.c \
	   SRCS/tokenization.c \
	   SRCS/trim_expand.c \
	   SRCS/valid.c \
	   INCLUDES/LIB/isalnum.c \
	   INCLUDES/LIB/memcpy.c \
	   INCLUDES/LIB/realloc.c \
	   INCLUDES/LIB/strchr.c \
	   INCLUDES/LIB/strdup.c \
	   INCLUDES/LIB/strtrim.c \
	   INCLUDES/LIB/strncmp.c \
	   INCLUDES/LIB/substr.c

OBJS = $(SRCS:.c=.o)
ECHO = echo -e
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

all : $(NAME)
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)
	@$(ECHO) "$(GREEN) executable PARSER created $(RESET)"

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