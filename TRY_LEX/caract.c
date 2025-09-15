void	is_pipe(t_lexem *head, t_cursor *cursor)
{
	t_token	token;

	token = get_token(cursor->input[cursor->position]);
	head = create_node(head, token, ft_substr(cursor->input, cursor->poition, 1));
	switch_token(token, cursor);
}

	is_double_quote()
{
	t_token	token;

	token = get_token(cursor->input[cursor->position]);
	head = create_node(head, token, ft_substr(cursor->input, cursor->poition, 1));
	switch_token(token, cursor);
}

	is_word_quote()
{
	if (cursor->prev == D_QUOTE)


}

	is_less_great()
{
	
}

	is_quote()
{

}

	is_word()
{

}
