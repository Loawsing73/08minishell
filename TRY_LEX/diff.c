#include "token.h"

t_token	get_token(char c)
{
	if (!s)
		return (ERROR);
//	if (s[0] == '\'')
//		return (QUOTE);
//	else if (s[0] == '"')
//		return (DOUBLE_QUOTE);
	else if (c == '<')
	{	
		if (s[1] == '<')
			return (D_LESS);
		return (LESS);
	}
	else if (c == '>')
	{
		if (s[1] == '>')
			return (D_GREAT);
		return (GREAT);
	}
	else if (c == '|')
		return (PIPE);
	else
		return (WORD);
}
//
void	switch_token(t_token token, t_cursor *cursor)
{
	cursor->prev = cursor->current;
	cursor->current = token;
}
//
t_lexem	create_node(t_lexem *head, t_token token, char *input)
{
	t_lexm	*node;

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
	parsing_input(t_cursor *cursor, char *input)
{
	t_lexem	*head;

	cursor->input = ft_strdup(intput);
	cursor->position = 0;
	cursor->current = ERROR;
	while (cursor->input[cursor->position])
	{
		if (cursor->input[cursor->position] == '|')
			is_pipe(head, cursor);
		else if (cursor->input[cursor->position] == '"')
			
		else if (cursor->input[cursor->position] == '\'')
			
		else if (cursor->input[cursor->position] == '>')
			
		else if (cursor->input[cursor->position] == '<')
			
		current->position++;
	}

}	
//



int	main()
{
	
	int		i = 0;
	char	*input;
	t_token	token;

	input = readline("enter : ");

}
