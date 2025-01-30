/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enivronmental.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:06:01 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/26 19:17:01 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;


/*
** ========================================================
** init_env
** ========================================================
*/

void init_env(t_env *envi)
{
	int count;
	int i;
	int len;
	int j;

	count = 0;
	while (environ[count] != NULL)
		count++;
	envi->env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envi->env)
		return ;
	i = 0;
	while (i < count)
	{
		len = 0;
		while (environ[i][len] != '\0')
			len++;
		envi->env[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!envi->env[i])
		{
			/* Ideally free partial allocations. */
			return ;
		}
		j = 0;
		while (j < len)
		{
			envi->env[i][j] = environ[i][j];
			j++;
		}
		envi->env[i][j] = '\0';
		i++;
	}
	envi->env[i] = NULL;
}

char	*get_env_value(const char *key, char **envp)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = 0;
	while (key[key_len] != '\0')
		key_len++;
	while (envp[i] != NULL)
	{
        /*
        ** Check if this line starts with 'key'.
        ** Example: if key = "PATH=", we compare up to length of "PATH=".
        ** ft_strncmp returns 0 if they match exactly for 'key_len' characters.
        */
		//printf("%s\n", envp[i]);
        if (ft_strncmp(envp[i], key, key_len) == 0)
			return (envp[i] + key_len);
		i++;
	}
	return (NULL);
}

