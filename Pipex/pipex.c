/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:59:14 by aortmann          #+#    #+#             */
/*   Updated: 2024/12/09 14:53:07 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(const char *cmd, int input_fd, int output_fd)
{
	if (input_fd != fileno(stdin))
	{
		if (dup2(input_fd, fileno(stdin)) == -1)
		{
			perror("dup2 input_fd");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}
	if (output_fd != fileno(stdout))
	{
		if (dup2(output_fd, fileno(stdout)) == -1)
		{
			perror("dup2 output_fd");
			exit(EXIT_FAILURE);
		}
		close(output_fd);
	}
	if (execlp("sh", "sh", "-c", cmd, NULL) == -1)
	{
		perror("execlp cmd");
		exit(EXIT_FAILURE);
	}
}

void	error_handling(int argc, int fd[2])
{
	if (argc != 5)
	{
		perror("Usage: file1 cmd1 cmd2 file2\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		perror("Pipe creation failed");
		exit(EXIT_FAILURE);
	}
}

void	create_child_process(char *argv[], int fd[2])
{
	char	*file1;
	char	*cmd1;
	int		input_fd;

	file1 = argv[1];
	cmd1 = argv[2];
	close(fd[0]);
	input_fd = open(file1, O_RDONLY);
	if (input_fd == -1)
	{
		perror("open file1");
		exit(EXIT_FAILURE);
	}
	exec_cmd(cmd1, input_fd, fd[1]);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	execute_parent(char *cmd, char *file, int fd[2])
{
	int	output_fd;
	int	status;

	close(fd[1]);
	output_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (output_fd == -1)
	{
		perror("open file");
		exit(EXIT_FAILURE);
	}
	exec_cmd(cmd, fd[0], output_fd);
	close(fd[0]);
	close(output_fd);
	wait(&status);
}

int	main(int argc, char *argv[])
{
	int		fd[2];
	pid_t	pid;

	error_handling(argc, fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		create_child_process(argv, fd);
	else
		execute_parent(argv[3], argv[4], fd);
	return (0);
}
