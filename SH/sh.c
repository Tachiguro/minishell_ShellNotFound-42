/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:21:34 by jherzog           #+#    #+#             */
/*   Updated: 2025/02/01 16:39:58 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	main(void)
{
	char	*line;
	t_token	*to_head;
	t_tree	*tr_head;

	line = NULL;
	to_head = NULL;
	using_history();
	while (1)
	{
		line = readline("$>");
		if (!line || !*line)
		{
			free(line);
			break ;
		}
		add_history(line);
		if (!is_correct_syntax(line))
		{
			free(line);
			print_error("Syntax is not correct!");
			continue ;
		}
		if (ft_strnstr(line, "exit", ft_strlen(line))) //i need exit with args, arg 1 == error code
		{
			exe(NULL, 1);
		}
		to_head = create_tokens(line);
		if (!to_head)
			print_error("Something is wrong... -> (!to_head)");
		tr_head = parse_tokens(&to_head);
		print_tokens(to_head);
		if (!tr_head)
			print_error("Something is wrong... -> (!tr_head)");
		free(line);
		exe(tr_head, 0);
		//break ; //>>>>>>>
	}
	print_tree(tr_head, 0);
	free_tokens(to_head);
	free_tree(tr_head);
	return (0);
}
