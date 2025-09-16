#include "token.h"

t_token	get_token(char c)
{
	if (!c)
		return (ERROR);
	if (c == '\'')
		return (QUOTE);
	else if (c == '"')
		return (DOUBLE_QUOTE);
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

	node = malloc(sizeof(t_lexem));
	node->token = token;
	node->input = input;
	node->next = NULL;
	if (head)
	{
		node->next = head;
		head = node;
		return (head);
	}
	return (node);
}

//
t_lexem *parsing_input(t_cursor *cursor, char *input)
{
	t_lexem	*head;

	cursor->input = ft_strdup(input);
	cursor->position = 0;
	cursor->current = ERROR;
	head = NULL;
	while (cursor->input[cursor->position])
	{
		while (cursor->input[cursor->position] == '\t' || cursor->input[cursor->position] == ' ')
			cursor->position++;
		if (cursor->input[cursor->position] == '|')	
			cursor->position = is_pipe(head, cursor);
		else if (cursor->input[cursor->position] == '"')
			cursor->position = is_double_quote(head, cursor);
		else if (cursor->input[cursor->position] == '\'')
			cursor->position = is_quote(head, cursor);
		else if (cursor->input[cursor->position] == '>')
			cursor->position = is_great(head, cursor);
		else if (cursor->input[cursor->position] == '<')
			cursor->position = is_less(head, cursor);
		else
		{	
			cursor->position = is_word(head, cursor);
			
		}
	}
	return (head);
}	
//



int	main()
{
	
	char		*input;
	t_lexem		*head;
	t_cursor	*cursor;

	input = readline("enter : ");
	head = parsing_input(cursor, input);
	while (head)
	{
		printf("%s - ", head->input);
		printf("%u -> ", head->token);
		head = head->next;	
	}
}
