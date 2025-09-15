#include "token.h"

t_token	get_token(char *s)
{
	if (!s)
		return (ERROR);
//	if (s[0] == '\'')
//		return (QUOTE);
//	else if (s[0] == '"')
//		return (DOUBLE_QUOTE);
	else if (s[0] == '<')
	{	
		if (s[1] == '<')
			return (D_LESS);
		return (LESS);
	}
	else if (s[0] == '>')
	{
		if (s[1] == '>')
			return (D_GREAT);
		return (GREAT);
	}
	else if (s[0] == '|')
		return (PIPE);
	else if (s[0] == '\n')
		return (NL);
	else
		return (WORD);
}
t_cursor	switch_token(t_token token, t_cursor *cursor)
{
	
}



	parsing_input(t_cursor *cursor, char *input)
{
	cursor->input = ft_strdup(intput);
	cursor->position = 0;
	cursor->current = ERROR;
	while (cursor->input[cursor->position])
	{
		if (cursor->input[cursor->position] == '|')
		{	
			
			creat_node(PIPE, ft_substr(cursor->input, cursor_poition, 1));
		}
		else if (cursor->input[cursor->position] == '"')
			creat_node(DOUBLE_QUOTE, ft_substr(cursor->input, cursor_poition, 1));
		else if (cursor->input[cursor->position] == '\'')
			creat_node(DOUBLE_QUOTE, ft_substr(cursor->input, cursor_poition, 1));
		else if (cursor->input[cursor->position] == '>')
			creat_node(GREAT, ft_substr(cursor->input, cursor_poition, 1));
	else if (cursor->input[cursor->position] == '<')
			creat_node(LESS, ft_substr(cursor->input, cursor_poition, 1));
	}

}	




int	main()
{
	
	int		i = 0;
	char	*input;
	t_token	token;

	input = readline("enter : ");

}
