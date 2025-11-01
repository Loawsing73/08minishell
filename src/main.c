#include "../includes/minishell.h"

int main(int ac, char **ag, char **env)
{
	char *input = NULL;
	char *joined;
	t_lexem *head;
	t_env	*new_env;
	//t_lexem *current;
	t_cursor cursor = {0};

	(void)ac;
	(void)ag;
	new_env = create_env(env);
	while (1)
	{
		input = readline("minishell >> ");
		if (*input == '\0')
			continue ;
		/*if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			add_history(input);
			free(input);
			break;
		}*/
		if (input)
			add_history(input);
		if (valid_input(ft_strtrim(input, " ")))
		{
			joined = concate_hell(input, new_env);
			// clean_neg_ascii(joined);
			//printf("%s\n", joined);
			head = parsing_input(&cursor, joined);
			//current = head;
			//while (current)
			//{
			//      printf("token = %u, input = %s\n", current->token, current->input);
			//      current = current->next;
			//}
			t_ast_node *ast = parse(head);
			if (ast)
			{
				//      print_ast(ast, 0);
				execute_ast(ast, new_env);
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

int main(int ac, char **ag, char **env_origin)
{
	t_global	global;
	char		*expanded_input;


	(void)ac;
	(void)ag;
	global.env = create_env(env_origin);
	while (1)
	{
		global.input = readline("minishell >> ");
		if (*global.input == '\0')
			continue ;
		if (ft_strncmp(global.input, "exit", ft_strlen(global.input)) == 0)
		{
			add_history(global.input);
			free(global.input);
			break;
		}
		if (global.input)
			add_history(global.input);
		if (valid_input(ft_strtrim(global.input, " ")))
		{
			expanded_input = concate_hell(expanded_input, &global);
			// clean_neg_ascii(joined);
			//printf("%s\n", joined);
			global.head = parsing_input(&global);
			//current = head;
			//while (current)
			//{
			//      printf("token = %u, global.input = %s\n", current->token, current->global.input);
			//      current = current->next;
			//}
			global.tree = parse(&global);
			if (global.tree)
			{
				//      print_ast(ast, 0);
				execute_ast(&global);
				free_ast(ast);
			}
			else
				printf("Erreur de parsing\n");
			free_lexem_list(head);
			free(joined);
		}
		else
			printf("invalid global.input\n");
		free(global.input);
		global.cursor.position = 0;
		global.cursor.current = ERROR;
		if (global.cursor.input)
		{
			free(global.cursor.input);
			global.cursor.input = NULL;
		}
	}
	clear_history();
	return (0);
}
