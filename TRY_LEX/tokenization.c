#include "token.h"

int	is_pipe_quotes(t_lexem **head, t_cursor *cursor)
{
	t_token	token;

	token = get_token(cursor->input[cursor->position]);
	if (token != PIPE)
		token = WORD;
	*head = create_node(*head, token, ft_substr(cursor->input, cursor->position, 1));
	switch_token(token, cursor);
	return (1);
}
//
int	is_word(t_lexem **head, t_cursor *cursor)
{
	t_token	token;
	int	index;
	int	pipe;
	int	dquote;
	int	quote;

	token = WORD;
	pipe = get_index(cursor->position, cursor->input, '|');
	quote = get_index(cursor->position, cursor->input, '\'');
	dquote = get_index(cursor->position, cursor->input, '"');
	if ((quote < get_space(cursor->position, cursor->input) && quote < pipe && quote < dquote && quote > -1))
		index = (quote-cursor->position);
	else if ((dquote < get_space(cursor->position, cursor->input) && dquote < pipe && dquote < quote && dquote > -1))
		index = (dquote-cursor->position);	
	else if ((pipe < get_space(cursor->position, cursor->input) && pipe < quote && pipe < dquote && pipe > -1))
		index = (pipe-cursor->position);
	else
		index = get_space(cursor->position, cursor->input)-cursor->position;
	*head = create_node(*head, token, ft_substr(cursor->input, cursor->position, index));
	return (switch_token(token, cursor), index);	
}
//
int	is_less(t_lexem **head, t_cursor *cursor)
{
	t_token	token;
	int 	position;
	
	position = cursor->position;
	token = get_token(cursor->input[position]);
	if (get_token(cursor->input[position +1]) == token)
	{		
		token = D_LESS;
		position++;
		*head = create_node(*head, token, ft_substr(cursor->input, cursor->position, 2));
		return (switch_token(token, cursor), 2);
	}
	else
	{
		*head = create_node(*head, token, ft_substr(cursor->input, cursor->position, 1));
		return (switch_token(token, cursor), 1);
	}
}
//
int	is_great(t_lexem **head, t_cursor *cursor)
{
	t_token	token;
	int 	position;
	
	position = cursor->position;
	token = get_token(cursor->input[position]);
	if (get_token(cursor->input[position+1]) == token)
	{		
		token = D_GREAT;
		position++;
		*head = create_node(*head, token, ft_substr(cursor->input, cursor->position, 2));
		return (switch_token(token, cursor), 2);
	}
	else
	{
		*head = create_node(*head, token, ft_substr(cursor->input, cursor->position, 1));
		return (switch_token(token, cursor), 2);
	}
}
//
int	get_index(int position, char *s, char c)
{
	while (s[position])
	{
		if (s[position] == c)
			return (position);
		position++;
	}
	return (280300);
}
//
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
//
t_token	get_token(char c)
{
	if (!c)
		return (ERROR);
	else if (c == '<')
		return (LESS);
	else if (c == '>')
		return (GREAT);
	else if (c == '|')
		return (PIPE);
	else
		return (ERROR);
}
//
void	switch_token(t_token token, t_cursor *cursor)
{
	cursor->previous = cursor->current;
	cursor->current = token;
}
//
t_lexem	*create_node(t_lexem *head, t_token token, char *input)
{
	t_lexem	*node;
	t_lexem	*current;

	node = malloc(sizeof(t_lexem));
	if (!node)
		return (head);
	node->token = token;
	node->input = ft_strdup(input);
	node->next = NULL;
	if (!head)
		return (node);
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
	return (head);
}


//
t_lexem *parsing_input(t_cursor *cursor, char *input)
{
	t_lexem	*head;

	cursor->input = ft_strdup(input);
	cursor->position = 0;
	cursor->previous = ERROR;
	head = NULL;
	while (cursor->input[cursor->position])
	{
		while (cursor->input[cursor->position] == '\t' || cursor->input[cursor->position] == ' ')
			cursor->position++;
		if (cursor->input[cursor->position] == '|')
			cursor->position += is_pipe_quotes(&head, cursor);
		else if (cursor->input[cursor->position] == '\'' || cursor->input[cursor->position] == '"')
			cursor->position += is_pipe_quotes(&head, cursor);
		else if (cursor->input[cursor->position] == '>')
			cursor->position += is_great(&head, cursor);
		else if (cursor->input[cursor->position] == '<')
			cursor->position += is_less(&head, cursor);
		else
			cursor->position += is_word(&head, cursor);
	}	
	return (head);
}	
//
void free_lexem_list(t_lexem *head)
{
    t_lexem *current;
    t_lexem *next;

    current = head;
    while (current)
    {
        next = current->next;
        free(current->input);  
		free(current);        
        current = next;
    }
}
//
int main(int ac, char **ag, char **env)
{
	char *input;
	char *joined;
	t_lexem *head;
	t_lexem *current;
	t_cursor cursor = {0};

	input = readline("enter : ");
	if (!input)
		return (1);
	if (valid_input(input))
	{
		joined = concate_hell(input, env);
		printf("%s\n", joined);
		head = parsing_input(&cursor, joined);
			current = head;
		while (current)
		{
			printf("Token: %u, Input: %s\n", current->token, current->input);
			current = current->next;
		}
		free_lexem_list(head);
		free(cursor.input);
	}
	else
		printf("invalid input\n");
	free(input);
	return (0);
}

