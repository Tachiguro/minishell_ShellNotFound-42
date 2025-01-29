/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:58:54 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/17 13:47:58 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	ft_unset(char *name)
{
	size_t	name_len;
	int		flag;
	int		i;
	int		j;

	i = 0;
	name_len = ft_strlen(name);
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], name, name_len) == 0
			&& environ[i][name_len] == '=')
		{
			j = i;
			while (environ[j] != NULL)
			{
				environ[j] = environ[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}
