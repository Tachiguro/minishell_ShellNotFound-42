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

#include "sh.h"

extern char	**environ;

/*
 * ft_cd_helper - Changes directory to the target directory and updates PWD.
 *
 * This function attempts to change the current working directory to
 * target_dir. It constructs an error message using ft_xappend if the
 * change fails, prints it using ft_fprintf, and returns. If successful,
 * it updates the PWD environment variable with the new working directory.
 */
void	ft_cd_helper(const char *target_dir)
{
	char	*str;
	char	*temp;
	char	*new_dir;
	
	str = ft_xappend("cd: ", (char *)target_dir, 0, 0);  // str becomes "cd: target_dir"
	temp = ft_xappend(str, ": ", 0, 1);                  // temp becomes "cd: target_dir: "
	str = ft_xappend(temp, strerror(errno), 0, 1);       // str becomes "cd: target_dir: <error message>", temp is freed
	if (chdir(target_dir) == -1) // if chdir fails
	{
		ft_fprintf(2, str);
		return ;
	}
	new_dir = getcwd(NULL, 0); // Get the new working directory
	if (new_dir != NULL)
	{
		setenv("PWD", new_dir, 1); // Update PWD with the new absolute path
		free(new_dir);            // Free memory allocated by getcwd
	}
	else
		ft_fprintf(2, "cd: unable to update PWD\n");
	if (str)
		free(str);
}

/*
 * ft_cd - Changes the current working directory.
 *
 * This function implements the built-in "cd" command. If no path is provided,
 * it attempts to change the directory to the HOME environment variable.
 * Otherwise, it uses the given path. It then calls ft_cd_helper to perform the
 * actual directory change and update the environment.
 */
void	ft_cd(const char *path)
{
	const char	*target_dir;

	if (path == NULL || path[0] == '\0') // if no path specified
	{
		target_dir = getenv("HOME"); // get HOME from the environment
		if (target_dir == NULL)
		{
			ft_fprintf(2, "cd: HOME not set\n"); // error if HOME not set
			return ;
		}
	}
	else
		target_dir = path;
	ft_cd_helper(target_dir);
}

/*
 * ft_echo - Prints a string to standard output, with or without a trailing newline.
 *
 * This function implements the built-in "echo" command. It accepts a string and a flag.
 * If the flag is "-n", it prints the string without a newline. Otherwise, it prints the
 * string followed by a newline.
 */
void	ft_echo(char *str, char *flag)
{
	if (ft_strcmp(flag, "-n")) // if flag is not "-n"
		printf("%s \n", str);
	else
	{
		printf("%s", str);
	}
}

/*
 * ft_env - Prints all environment variables.
 *
 * This function implements the built-in "env" command. It iterates through the
 * global environ array and prints each environment variable on a new line.
 */
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

/*
 * ft_unset - Removes an environment variable.
 *
 * This function implements the built-in "unset" command. It searches the global
 * environ array for an environment variable whose name matches the provided name.
 * If found, it shifts the remaining environment variables up to remove the entry.
 */
void	ft_unset(char *name, t_env *envi)
{
	size_t	name_len;
	int		i;
	int		j;

	i = 0;
	name_len = ft_strlen(name);
	while (envi->env[i] != NULL)
	{
		if (ft_strncmp(envi->env[i], name, name_len) == 0
			&& envi->env[i][name_len] == '=')
		{
			j = i;
			while (envi->env[j] != NULL)
			{
				envi->env[j] = envi->env[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}
