/*static void	skip_whitespace(const char *input, int *i)
{
	while (input[*i] && isspace((unsigned char)input[*i]))
	{
		(*i)++;
	}
}

char	*read_input(void)
{
	char	*line;

	line = readline("minishell> ");
	return (line);
}

void	shell_loop(t_pvars	*pvars, t_svars *svars)
{
	svars->status = 1;
	svars->input = read_input();
	while (svars->status)
	{
		if (!svars->input)
			break ;
		if (*svars->input)
			add_history(svars->input);
		svars->args = parse_input(svars->input);
		svars->status = execute_command(svars->args);
		free (svars->input);
		free(svars->args);
	}
}

void	init(void)
{
	t_pvars	pvars;
	t_svars	svars;

	pvars.len = 0;
	pvars.count = 0;
	pvars.i = 0;
	pvars.tokens = NULL;
	svars.args = NULL;
	svars.input = NULL;
	svars.status = 0;
	shell_loop(&pvars, &svars);
}

int	main(void)
{
	init();
	return (EXIT_SUCCESS);
}*/