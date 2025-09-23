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
	PIPE,
	QUOTE,
	DOUBLE_QUOTE,
	EXPAND,
	ERROR
}	t_token;

typedef struct	s_lexem
{
	t_token	token;
	char	*input;
	struct s_lexem	*next;
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
char	*ft_strdup(char *s1);

int	is_pipe_quotes_exp(t_lexem **head, t_cursor *cursor);
int	is_word(t_lexem **head, t_cursor *cursor);
int	is_great(t_lexem **head, t_cursor *cursor);
int	is_less(t_lexem **head, t_cursor *cursor);
int	get_index(int position, char *s, char c);
int	valid_input(char *input);
t_token	get_token(char c);
void	switch_token(t_token token, t_cursor *cursor);
t_lexem	*create_node(t_lexem *head, t_token token, char *input);
t_lexem *parsing_input(t_cursor *cursor, char *input);
int	get_space(int position, char *s);
void free_lexem_list(t_lexem *head);
		
#endif
