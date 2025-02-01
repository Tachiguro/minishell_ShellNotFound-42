/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:32:28 by jherzog           #+#    #+#             */
/*   Updated: 2025/02/01 16:44:01 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static t_token	*create_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free (token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **head, t_token *token)
{
	t_token	*last;

	if (!*head)
		*head = token;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = token;
	}
}

static void	special_token(char **line, t_token **head)
{
	if (**line == '>')
	{
		if (*(*line + 1) == '>')
		{
			add_token(head, create_token(T_APPEND, ">>"));
			(*line)++;
		}
		else
			add_token(head, create_token(T_OUT, ">"));
	}
	else if (**line == '<')
		add_token(head, create_token(T_IN, "<"));
	else if (**line == '|')
		add_token(head, create_token(T_PIPE, "|"));
	(*line)++;
}

static void	other_token(char **line, t_token **head)
{
	char	*start;
	bool	in_quote;
	char	quote_char;

	start = *line;
	in_quote = false;
	quote_char = '\0';
	while (**line)
	{
		if (!in_quote && (**line == '\'' || **line == '\"'))
		{
			in_quote = true;
			quote_char = **line;
		}
		else if (in_quote && (**line == quote_char))
			in_quote = false;
		else if (!in_quote && ft_strchr(" \t\n><|", **line))
			break ;
		(*line)++;
	}
	add_token(head, create_token(T_WORD, ft_substr(start, 0, *line - start)));
}

t_token	*create_tokens(char *line)
{
	t_token	*head;

	head = NULL;
	while (*line)
	{
		while (*line && ft_strchr(" \t\n", *line))
			line++;
		if (*line == '\0')
			break ;
		if (ft_strchr("><|", *line))
			special_token(&line, &head);
		else
			other_token(&line, &head);
	}
	return (head);
}
