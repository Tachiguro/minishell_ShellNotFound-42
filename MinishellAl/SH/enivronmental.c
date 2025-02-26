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

#include "sh.h"

extern char **environ;


/*
** ========================================================
** init_env
** ========================================================
*/
/*
 * count_env_vars - Returns the number of environment variables in 'environ'.
 */
static int count_env_vars(void)
{
    int count;

    count = 0;
    while (environ[count] != NULL)
    {
        count++;
    }
    return (count);
}

/*
 * duplicate_env_entry - Duplicates a single environment string.
 *
 * Allocates memory for a new string and copies all characters from src.
 * Returns the duplicated string, or NULL on allocation failure.
 */
static char *duplicate_env_entry(const char *src)
{
    int     len;
    int     i;
    char    *dest;

    len = 0;
    while (src[len] != '\0')
        len++;
    dest = malloc(sizeof(char) * (len + 1));
    if (!dest)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

/*
 * init_env - Initializes the environment in t_env by duplicating 'environ'.
 *
 * This function allocates an array for 'envi->env' large enough to hold all
 * environment variables plus a terminating NULL pointer. It duplicates each
 * environment string using duplicate_env_entry. On allocation failure, it frees
 * any allocated memory and returns.
 */
void init_env(t_env *envi)
{
    int count;
    int i;

    count = count_env_vars();
    envi->env = malloc(sizeof(char *) * (count + 1));
    if (!envi->env)
        return;
    i = 0;
    while (i < count)
    {
        envi->env[i] = duplicate_env_entry(environ[i]);
        if (!envi->env[i])
        {
            while (--i >= 0)
                free(envi->env[i]);
            free(envi->env);
            return;
        }
        i++;
    }
    envi->env[i] = NULL;
}


char	*get_env_value(const char *key, char **envp)
{
	int		i;
	int		key_len;
	char	*value;

	i = 0;
	key_len = 0;
	while (key[key_len] != '\0')
		key_len++;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
		{
			value = ft_strdup(envp[i] + key_len);
			if (!value)
				return (NULL); // Handle memory allocation failure
			return (value);
		}
		i++;
	}
	return (NULL);
}


