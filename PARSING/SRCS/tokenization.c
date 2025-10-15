#include "../INCLUDES/token.h"

int	is_pipe(t_lexem **head, t_cursor *cursor)
{
	t_token	token;

	token = get_token(cursor->input[cursor->position]);
	if (token != PIPE)
		token = WORD;
	*head = create_node(*head, token,
			ft_substr(cursor->input, cursor->position, 1));
	switch_token(token, cursor);
	return (1);
}

int	is_word(t_lexem **head, t_cursor *cu)
{
	t_token	token;
	t_index	data;
	int		index;

	token = WORD;
	data.pipe = get_index(cu->position, cu->input, '|') - cu->position;
	data.less = get_index(cu->position, cu->input, '<') - cu->position;
	data.great = get_index(cu->position, cu->input, '>') - cu->position;
	data.space = get_space(cu->position, cu->input) - cu->position;
	if (cu->current == GREAT || cu->current == D_GREAT || cu->current == LESS)
	{
		token = IO_LOCA;
	 	index = data.space;
	}
	else if (cu->current == D_LESS)
	{
		token = DELIMITER;
	 	index = data.space;
	}
	else if (cu->current == ERROR)
		index = data.space;
	else if  (data.pipe < data.less && data.pipe < data.great && data.pipe > -1 && cu->current != PIPE)
		index = data.pipe;
	else if  (data.less < data.pipe && data.less < data.great && data.less > -1)
		index = data.less;
	else if  (data.great < data.pipe && data.great < data.less && data.great > -1)
		index = data.great;
	else
		index = data.space;
	*head = create_node(*head, token,
			ft_substr(cu->input, cu->position, index));
	return (switch_token(token, cu), index);
}

int	is_less(t_lexem **head, t_cursor *cursor)
{
	t_token	token;
	int		position;

	position = cursor->position;
	token = get_token(cursor->input[position]);
	if (get_token(cursor->input[position +1]) == token)
	{
		token = D_LESS;
		position++;
		*head = create_node(*head, token,
				ft_substr(cursor->input, cursor->position, 2));
		return (switch_token(token, cursor), 2);
	}
	else
	{
		*head = create_node(*head, token,
				ft_substr(cursor->input, cursor->position, 1));
		return (switch_token(token, cursor), 1);
	}
}

int	is_great(t_lexem **head, t_cursor *cursor)
{
	t_token	token;
	int		position;

	position = cursor->position;
	token = get_token(cursor->input[position]);
	if (get_token(cursor->input[position + 1]) == token)
	{
		token = D_GREAT;
		position++;
		*head = create_node(*head, token,
				ft_substr(cursor->input, cursor->position, 2));
		return (switch_token(token, cursor), 2);
	}
	else
	{
		*head = create_node(*head, token,
				ft_substr(cursor->input, cursor->position, 1));
		return (switch_token(token, cursor), 1);
	}
}

int	get_index(int position, char *s, char c)
{
	while (s[position])
	{
		if (s[position] == c)
			return (position);
		position++;
	}
	return (-280300);
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

void	switch_token(t_token token, t_cursor *cursor)
{
	cursor->previous = cursor->current;
	cursor->current = token;
}

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

t_lexem *parsing_input(t_cursor *cursor, char *input)
{
	t_lexem	*head;

	cursor->input = ft_strdup(input);
	cursor->position = 0;
	cursor->previous = ERROR;
	cursor->current = ERROR;
	head = NULL;
	while (cursor->input[cursor->position])
	{
		while (cursor->input[cursor->position] == '\t'
			|| cursor->input[cursor->position] == ' ')
			cursor->position++;
		if (cursor->input[cursor->position] == '|')
			cursor->position += is_pipe(&head, cursor);
		else if (cursor->input[cursor->position] == '>')
			cursor->position += is_great(&head, cursor);
		else if (cursor->input[cursor->position] == '<')
			cursor->position += is_less(&head, cursor);
		else
			cursor->position += is_word(&head, cursor);
	}
	return (head);
}

void	free_lexem_list(t_lexem *head)
{
	t_lexem	*current;
	t_lexem	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->input);
		free(current);
		current = next;
	}
}
// static void	clean_neg_ascii(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] < 0)
// 			s[i] = -s[i];
// 		i++;
// 	}
// }

int main(int ac, char **ag, char **env)
{
	char *input;
	char *joined;
	t_lexem *head;
	//t_lexem *current;
	t_cursor cursor = {0};
	
	(void)ac;
	(void)ag;
	create_env(env);
	while (1)
	{
		input = readline("minishell >> ");
		if (!input)
		{
			clear_history();
			return (1);
		}
		if (ft_strncmp(input, "exit", 4) == 0)
		{
    		add_history(input);
			free(input);
			break;
		}
		if (*input)
			add_history(input);
		if (valid_input(ft_strtrim(input, " ")))
		{
			joined = concate_hell(input, env);
			// clean_neg_ascii(joined);
			//printf("%s\n", joined);
			head = parsing_input(&cursor, joined);
			//current = head;
			//while (current)
			//{
			//	printf("token = %u, input = %s\n", current->token, current->input);
			//	current = current->next;
			//}
			t_ast_node *ast = parse(head);
			if (ast)
			{
			//	print_ast(ast, 0);
				execute_ast(ast, env);
				free_ast(ast);
			}
			else
				printf("Erreur de parsing\n");
			free_lexem_list(head);
			free(joined);
		}
		else
			printf("invalid input\n");
		free(input);
		cursor.position = 0;
		cursor.current = ERROR;
		if (cursor.input)
		{
			free(cursor.input);
			cursor.input = NULL;
		}
	}
	clear_history();
	return (0);
}
