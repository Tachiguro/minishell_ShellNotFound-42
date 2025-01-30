/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:38:48 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/26 21:19:44 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	ft_cd_helper(const char *target_dir)
{
	char	*str;
	char	*temp;
	char	*new_dir;
	
	str = ft_xappend("cd: ", (char *)target_dir, 0, 1);  //str is now cd: target_dir
	temp = ft_xappend(str, ": ", 0, 1);//temp is now cd: target_dir: _
	str = ft_xappend(temp, strerror(errno), 0, 1);//str is now cd: target_dir: strerro temp is freed
	if (chdir(target_dir) == -1) //if cd failed
	{
		ft_fprintf(2, str);
		return ;
	}
    // Update env variable
	new_dir = getcwd(NULL, 0); // Get the new working directory
	if (new_dir != NULL)
	{
		setenv("PWD", new_dir, 1); // Update PWD<-(absolute path to working dir) in the environment
		free(new_dir); // Free memory of getcwd
	}
	else
		ft_fprintf(2, "cd: unable to update PWD\n");
}

void	ft_cd(const char *path)
{
	const char	*target_dir;

	if (path == NULL || path[0] == '\0') //if no path is specified
	{
		target_dir = getenv("HOME"); //set new path to home from env variables
		if (target_dir == NULL)
		{
			ft_fprintf(2, "cd: HOME not set\n"); //errror if home is not set
			return ;
		}
	}
	else
		target_dir = path;
	ft_cd_helper(target_dir);
}

void	ft_echo(char *str, char *flag)
{
	if (ft_strcmp(flag, "-n")) //flag != -n
		printf("%s \n", str);
	else
	{
		printf("%s", str);
	}
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

void	ft_unset(char *name)
{
	size_t	name_len;
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
