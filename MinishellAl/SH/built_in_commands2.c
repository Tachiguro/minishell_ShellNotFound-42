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

/*
 * close_fds - Closes all file descriptors from 3 to 1023.
 *
 * This function iterates over file descriptor numbers starting at 3 (skipping
 * standard input, output, and error) up to 1023 and closes each one.
 * It is used during cleanup to ensure that no stray file descriptors remain open.
 */
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

/*
 * ft_exit - Exits the shell with an optional status code.
 *
 * This function handles the built-in "exit" command. It prints an exit message,
 * validates that the provided exit status (if any) is numeric, and then performs
 * cleanup by closing file descriptors and freeing allocated resources before exiting.
 * If the argument is non-numeric, it prints an error message and exits with status 255.
 * If no exit status is provided, it exits with status 0.
 */
int	ft_exit(char **args, t_str *str)
{
	int	status;
	int	i;

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
				exit(255); // 255 signals a severe or unhandled error.
			}
			i++;
		}
		status = atoi(args[1]);
	}
	cleanup(str);
	close_fds();
	exit(status);
}

/*
 * ft_pwd - Prints the current working directory.
 * This function retrieves the current working directory using getcwd.
 * If successful, it prints the directory path to standard output and frees
 * the allocated buffer. In case of an error, it prints an error message and
 * returns a non-zero status code.
 */
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
