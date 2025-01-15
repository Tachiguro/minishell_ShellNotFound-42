/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:03:54 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/15 17:21:48 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_fd(void)
{
	int fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

ft_exit(char **args)
{
	int	status;
	int	i;

	if (args[1] == NULL)
		status = 0;
	else
	{
		i = 0;
		while (args[1][i] != '\0')
		{
			if (args[1][i] < '0' || args[1][i] > '9')
			{
				printf("exit: numeric argument required\n");
				close_fd();
				exit(255); //255 is the largest possible exit code on many systems and is often used to signal a severe or unhandled error.
			}
			i++;
		}
		status = atoi(args[1]);
	}
	close_all_fds();
	exit(status);
}

