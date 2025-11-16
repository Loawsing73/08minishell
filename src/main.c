#include "../includes/minishell.h"

int main(int ac, char **ag, char **env)
{
	char *input = NULL;
	char *joined;
	t_lexem *head;
	t_env	*new_env;
	//t_lexem *current;
	t_cursor cursor = {0};
	struct sigaction control_c;

	(void)ac;
	(void)ag;
	control_c.sa_handler = handle_c;
	sigemptyset(&control_c.sa_mask);
	control_c.sa_flags = 0;
	sigaction(SIGINT, &control_c, NULL);
    control_c.sa_handler = SIG_IGN;
    sigemptyset(&control_c.sa_mask);
    control_c.sa_flags = 0;
    sigaction(SIGQUIT, &control_c, NULL);
	new_env = create_env(env);
	while (1)
	{
		input = readline("minishell >> ");
		if (!input)
			break;
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
