#include "token.h"

int	is_pipe_quotes(t_lexem *head, t_cursor *cursor)
{
	t_token	token;

	token = get_token(cursor->input[cursor->position]);
	head = create_node(head, token, ft_substr(cursor->input, cursor->position, 1));
	switch_token(token, cursor);
	return (cursor->position++);
}

int	is_word(t_lexem *head, t_cursor *cursor)
{
	t_token	token;
	int	index;

	token = WORD;
	if (cursor->previous == DOUBLE_QUOTE)
	{	
		index = get_index(cursor->position, cursor->input, '"')-cursor->position;
		if (index < 0)
			token = ERROR;;
		head = create_node(head, token, ft_substr(cursor->input, cursor->position, index));
	}
	else if (cursor->previous == QUOTE)
	{	
		index = get_index(cursor->position, cursor->input, '\'')-cursor->position;
		if (index < 0)
			token = ERROR;
		head = create_node(head, token, ft_substr(cursor->input, cursor->position, index));
	}
	else
	{
		index = get_space(cursor->position, cursor->input)-cursor->position;
		head = create_node(head, token, ft_substr(cursor->input, cursor->position, index));
		return (switch_token(token, cursor), index+1);
	}	
	return (switch_token(token, cursor), index-1);	
}

int	is_great(t_lexem *head, t_cursor *cursor)
{
	t_token	token;
	int 	position;
	
	token = get_token(cursor->input[position]);
	position = cursor->position;
	if (get_token(cursor->input[position+1] == token))
	{		
		token = D_GREAT;
		position = position+1;
	}
	head = create_node(head, token, ft_substr(cursor->input, cursor->position, 1));
	switch_token(token, cursor);
	return (position+1);
}

int	is_less(t_lexem *head, t_cursor *cursor)
{
	t_token	token;
	int 	position;
	
	token = get_token(cursor->input[position]);
	position = cursor->position;
	if (get_token(cursor->input[position+1] == token))
	{		
		token = D_LESS;
		position = position+1;
	}
	head = create_node(head, token, ft_substr(cursor->input, cursor->position, 1));
	switch_token(token, cursor);
	return (position+1);
}

int	get_index(int position, char *s, char c)
{
	while (s[position])
	{
		if (s[position] == c)
			return (position);
		position++;
	}
	return (-1);
}

int	get_space(int position, char *s)
{
	while (s[position])
	{
		if (s[position] == ' ')
			return (position);
		position++;
	}
	return (ft_strlen(s));
}
