/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:44:33 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/26 19:10:55 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_fprintf(int stream, char *str)
{
	int	len;

	len = ft_strlen(str);
	write(stream, str, len);
}

/*
** ========================================================
** 6) is_built_in
**    Return 1 if it's a builtin, 0 otherwise.
**    Use !ft_strcmp to check for equality.
** ========================================================
*/
int is_built_in(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/*
** ========================================================
** 2) contains_slash
** ========================================================
*/
int contains_slash(char *cmd)
{
	while (*cmd != '\0')
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}
