/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:54:18 by jherzog           #+#    #+#             */
/*   Updated: 2025/02/01 16:39:08 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	parse_redirections(t_token **head, t_tree *cmd_node)
{
	t_type	redir_type;
	char	*filename;

	while (*head && ((*head)->type == T_IN || (*head)->type == T_OUT
			|| (*head)->type == T_APPEND))
	{
		redir_type = (*head)->type;
		*head = (*head)->next;
		if (!*head || (*head)->type != T_WORD)
		{
			print_error("ERROR redirection");
			break ;
		}
		filename = ft_strdup((*head)->value);
		printf("!!!!!!!!!!!!!!%s\n", filename);
		*head = (*head)->next;
		if (redir_type == T_IN)
		{
			if (cmd_node->infile)
				free(cmd_node->infile);
			cmd_node->infile = filename;
		}
		else if (redir_type == T_OUT)
		{
			if (cmd_node->outfile)
				free(cmd_node->outfile);
			cmd_node->outfile = filename;
			cmd_node->append = 0;
		}
		else if (redir_type == T_APPEND)
		{
			if (cmd_node->outfile)
				free(cmd_node->outfile);
			cmd_node->outfile = filename;
			cmd_node->append = 1;
		}
	}
}

static t_tree *parse_command(t_token **head)
{
    t_tree  *node;
    t_token *tmp;
    int     count;
    int     i;

    count = 0;
    tmp = *head;
    while (tmp && tmp->type == T_WORD)
    {
        count++;
        tmp = tmp->next;
    }
    if (count == 0)
        return (NULL);
    node = malloc(sizeof(t_tree));
    if (!node)
        return (NULL);
    /* Use ft_calloc to initialize all pointers to NULL */
    node->args = ft_calloc(count + 1, sizeof(char *));
    if (!node->args)
    {
        free(node);
        return (NULL);
    }
    i = 0;
    while (*head && (*head)->type == T_WORD)
    {
        node->args[i] = ft_strdup((*head)->value);
        i++;
        *head = (*head)->next;
    }
    node->args[i] = NULL;
    node->type = T_WORD;
    node->file_type = 0;
    node->infile = NULL;
    node->outfile = NULL;
    node->append = 0;
    node->left = NULL;
    node->right = NULL;
    parse_redirections(head, node);
    return (node);
}


t_tree	*parse_tokens(t_token **head) //<- brainfuck recursiv
{
	t_tree	*cmd_node;
	t_tree	*pipe_node;

	if (!head || !*head)
		return (NULL);
	cmd_node = parse_command(head);
	if (!cmd_node)
		return (NULL);
	if (*head && (*head)->type == T_PIPE)
	{
		pipe_node = malloc(sizeof(t_tree));
		if (!pipe_node)
			return (cmd_node);
		pipe_node->type = T_PIPE;
		pipe_node->file_type = 0;
		pipe_node->args = NULL;
		pipe_node->left = cmd_node;
		*head = (*head)->next;
		pipe_node->right = parse_tokens(head);
		return (pipe_node);
	}
	return (cmd_node);
}

void	print_tree(t_tree *root, int indent)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!root)
		return ;
	while (i < indent)
	{
		ft_printf("    ");
		i++;
	}
	if (root->type == T_WORD)
	{
		ft_printf("CMD: ");
		if (root->args)
		{
			j = 0;
			while (root->args[j])
			{
				ft_printf("%s ", root->args[j]);
				j++;
			}
		}
		if (root->infile)
			ft_printf("IN %s ", root->infile);
		if (root->outfile)
		{
			if (root->append)
				ft_printf("APPEND %s ", root->outfile);
			else
				ft_printf("OUT %s ", root->outfile);
		}
		ft_printf("\n");
	}
	else if (root->type == T_PIPE)
	{
		ft_printf("PIPE\n");
	}
	print_tree(root->left, indent + 1);
	print_tree(root->right, indent + 1);
}

void free_tree(t_tree *root)
{
    int i;

    if (!root)
        return;
    if (root->args)
    {
        i = 0;
        while (root->args[i])
        {
            free(root->args[i]);
            i++;
        }
        free(root->args);
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}


