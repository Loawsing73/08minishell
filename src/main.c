#include "../includes/minishell.h"

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
		if (valid_input(ft_strtrim(global.input, " "))) //strtrim a free
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
				free_ast(global.tree);
			}
			else
				printf("Erreur de parsing\n");
			free_lexem_list(&global);
			free(expanded_input);
		}
		else
			printf("invalid input\n");
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
