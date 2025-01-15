/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:13:12 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/15 18:38:59 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	ft_cd(const char *path)
{
	const char	*target_dir;
	char		*current_dir;
	char		new_dir;

	if (path == NULL || path[0] == '\0') //if no path is specified
	{
		target_dir = getenv("HOME"); //set new path to home from env variables
		if (target_dir == NULL)
		{
			printf("cd: HOME not set\n"); //errror if home is not set
			return ;
		}
	}
	else
		target_dir = path;
	if (chdir(target_dir) == -1) //if cd failed
	{
		printf(stderr, "cd: %s: %s\n", target_dir, strerror(errno));
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
		printf("cd: unable to update PWD\n");
}