#include "../../includes/minishell.h"
/* si | alors crée node avce token PIPE*/
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
/*si >, <, >> alors token IO_LOCA car redirection
si << alors token DELIMITER
sinon, on va jusqu'au premier oprateur et créee node word avec substr de l'input*/
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
/*si < crée node LESS
si << crée node DLESS*/
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
/*si >crée node GREAT
si >> crée node DGREAT*/
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
/*ret index de char c dans string*/
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
/*ret index de premier espace rencontré*/
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
/*token d'opérateur*/
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
/*actualise token actuel et token précédent*/
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
/*fonction principale de pasring de l'output :
tant que espace, avance
si |, crée node PIPE
si <, <<, >, >> crée node correpondant
else c'est un word*/
t_lexem *parsing_input(t_global *global)
{
	global->cursor->input = ft_strdup(global.input); //free global.iput
	global->cursor->position = 0;
	global->cursor->previous = ERROR;
	global->cursor->current = ERROR;
	global->head = NULL;
	while (global->cursor->input[global->cursor->position])
	{
		while (global->cursor->input[global->cursor->position] == '\t'
			|| global->cursor->input[global->cursor->position] == ' ')
			global->cursor->position++;
		if (global->cursor->input[global->cursor->position] == '|')
			global->cursor->position += is_pipe(global);
		else if (global->cursor->input[global->cursor->position] == '>')
			global->cursor->position += is_great(global);
		else if (global->cursor->input[global->cursor->position] == '<')
			global->cursor->position += is_less(global);
		else
			global->cursor->position += is_word(global);
	}
	return (global->head);
}

void	free_lexem_list(t_global *global)
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
