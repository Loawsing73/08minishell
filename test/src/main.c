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
			//      printf("token = %u, input = %s\n", current->token, current->input);
			//      current = current->next;
			//}
			t_ast_node *ast = parse(head);
			if (ast)
			{
				//      print_ast(ast, 0);
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
