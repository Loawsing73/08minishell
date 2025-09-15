#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef	enum e_token
{
	WORD = 0,
	IO_LOCA,
	D_LESS,
	D_GREAT,
	LESS,
	GREAT,
	NL,
	PIPE,
//	R_PARENT,
//	L_PARENT,
//	R_BRACKETS,
//	L_BRACKETS,
//	QUOTE,
//	DOUBLE_QUOTE,
	ERROR
}	t_token;

typedef struct	s_lexem
{
	t_token	token;
	char	*input;
	t_lexem	*next;
}	t_lexem;
typedef	struct	s_cursor
{
	int	position;
	char	*input;
	t_token	current;
	t_token	previous;
}	t_cursor;

char	*ft_substr(char *s, size_t start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(char *s);
ssize_t	get_index(char *s);
char	**ft_split_pipe(char *s);

#endif
