/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:38:48 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/18 20:04:42 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

int	ft_exit(char **args, t_str *str)
{
	int	status;
	int	i;

	printf("Reached exit\n");
	if (!args || args[1] == NULL)
		status = 0;
	else
	{
		i = 0;
		while (args[1][i] != '\0')
		{
			if (args[1][i] < '0' || args[1][i] > '9')
			{
				printf("exit: numeric argument required\n");
				close_fds();
				cleanup(str);
				exit(255); //255 is the largest possible exit code on many systems and is often used to signal a severe or unhandled error.
			}
			i++;
		}
		status = atoi(args[1]);
	}
	cleanup(str);
	close_fds();
	exit(status);
}

int	ft_pwd(void)
{
	char	*buffer;
	size_t	size;

	buffer = NULL;
	size = 0;
	buffer = getcwd(buffer, size);
	if (buffer == NULL)
	{
		perror("Error retrieving current directory");
		return (1);
	}
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}