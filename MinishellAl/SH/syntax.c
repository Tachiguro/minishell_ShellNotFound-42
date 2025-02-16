/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:12:53 by jherzog           #+#    #+#             */
/*   Updated: 2025/02/01 16:42:32 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static bool	is_valid_char_in_pos(const char *l)
{
	int	len;

	len = ft_strlen(l);
	if (len == 0)
		return (true);
	if (l[0] == '<' || l[0] == '>' || l[0] == ')' || l[0] == '|'
		|| l[len - 1] == '<' || l[len - 1] == '>' || l[len - 1] == ')'
		|| l[len - 1] == '|')
		return (false);
	return (true);
}

static bool	are_quotes_right(const char *l)
{
	int		i;
	bool	in_double_quote;
	bool	in_single_quote;

	in_double_quote = false;
	in_single_quote = false;
	i = 0;
	while (l[i] != '\0')
	{
		if (l[i] == '\\' && l[i + 1] != '\0' && (l[i + 1] == '\"'
				|| l[i + 1] == '\''))
		{
			i += 2;
			continue ;
		}
		if (l[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (l[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		i++;
	}
	if (in_double_quote || in_single_quote)
		return (false);
	return (true);
}

bool	is_correct_syntax(const char *l)
{
	if (!is_valid_char_in_pos(l))
		return (false);
	if (!are_quotes_right(l))
		return (false);
	return (true);
}
