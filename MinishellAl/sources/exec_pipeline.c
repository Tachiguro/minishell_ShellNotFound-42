/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:08:53 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/29 14:13:49 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/libft.h"

void exec_command(t_exec_pipe *cmd_node, t_str *str)
{
	char *fullpath;

	// Find the executable path
	printf("execute %s !!!!!!!!!!!!!!!!!\n", cmd_node->cmd);
	fullpath = find_executable_path(cmd_node->cmd, str);
	if (!fullpath)
	{
		fprintf(stderr, "minishell: command not found: %s\n", cmd_node->cmd);
		exit(127); // Common exit code for command not found
	}
    // Execute the command
	execve(fullpath, cmd_node->args, str->environs->env);
    // If execve returns, an error occurred
	perror("execve");
	exit(EXIT_FAILURE);
}

void exec_pipe(t_str *stru)
{
	t_exec_pipe	*current;
	int			pipefd[2];    // File descriptors for the current pipe
	int			prev_fd_in;   // Read end of the previous pipe
	pid_t		pid;
	int			status;

    prev_fd_in = -1;            // Initialize to indicate no previous pipe
    current = stru->xpipe;      // Start with the first command

	while (current != NULL && !ft_strcmp(current->re, "|"))
	{
        // Check if the current command has a next command
		if (current->next)
		{
			printf("NEXT CMD FOUND it is %s !!!\n", current->next->cmd);
			// Create a new pipe for the next command
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
            // No next command; set pipefd to invalid
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
        // Fork a child process to execute the current command
		pid = fork();
		if (pid < 0) // Fork failed
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // Child process
		{
            // If there's a previous pipe, redirect STDIN to it
			if (prev_fd_in != -1)
			{
				if (dup2(prev_fd_in, STDIN_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(prev_fd_in); // Close the duplicated fd
			}
            // If there's a next command with a pipe, redirect STDOUT to pipefd[1]
			if (pipefd[1] != -1)
			{
				printf("CHILD EXECUTE!!!!\n");
				if (dup2(pipefd[1], STDOUT_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(pipefd[0]); // Close unused read end
				close(pipefd[1]); // Close duplicated write end
			}
			printf("CHILD EXECUTE!!!!\n");
			// Execute the current command
			exec_command(current, stru);
            // If exec_command returns, an error occurred
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else // Parent process
		{
            // Close the write end of the current pipe in the parent
			if (pipefd[1] != -1)
				close(pipefd[1]);
            // Close the previous pipe's read end as it's no longer needed
			if (prev_fd_in != -1)
				close(prev_fd_in);
            // The next command will read from the current pipe's read end
			prev_fd_in = pipefd[0];
		}
        // Move to the next command in the pipeline
		current = current->next;
        // If the next command doesn't have a pipe, break the loop
		if (!current || ft_strcmp(current->re, "|"))
		{
			printf("NO MORE PIPE FOUND!!!\n");
			break ;
		}
	}
    // Execute the last command outside the loop
	if (current != NULL) // There is a last command to execute
	{
		pid = fork();
		if (pid < 0) // Fork failed
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // Child process for the last command
		{
            // If there's a previous pipe, redirect STDIN to it
			if (prev_fd_in != -1)
			{
				if (dup2(prev_fd_in, STDIN_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(prev_fd_in); // Close the duplicated fd
			}
            // No pipe after the last command; STDOUT remains unchanged
            // Execute the last command
			exec_command(current, stru);
            // If exec_command returns, an error occurred
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else // Parent process
		{
            // Close the read end of the last pipe as it's no longer needed
			if (prev_fd_in != -1)
				close(prev_fd_in);
            // Wait for the last child process to finish
			waitpid(pid, &status, 0);
		}
	}
    // Wait for all previous child processes to finish to prevent zombies
    // This loop waits for all children except the last one, which was already waited for
	current = stru->xpipe;
	while (current != NULL && !ft_strcmp(current->re, "|"))
	{
		wait(&status);
		current = current->next;
	}
}


void	exec_pipeline(t_str *stru)
{
	// printf("EXEC PIPELINE REACHED!!!!!!!!\n");
	// exit(0);
	while (stru->xpipe)  // while list exists loop trough it
	{
		if (stru->xpipe->next && !ft_strcmp(stru->xpipe->re, "|")) //handle pipes first
			exec_pipe(stru);
		else if (((stru->xpipe->next && !ft_strcmp(stru->xpipe->re, "<<")))) // << should be given a delimiter, then read the input until a line containing thedelimiter is seen. However, it doesn’t have to update the history
			printf("<<\n");
		else if (((stru->xpipe->next && !ft_strcmp(stru->xpipe->re, ">>")))) //>> should redirect output in append mode.
			printf(">>\n");
		else if (((stru->xpipe->next && !ft_strcmp(stru->xpipe->re, "<")))) //< should redirect input.
			printf("<\n");
		else if (((stru->xpipe->next && !ft_strcmp(stru->xpipe->re, ">")))) //◦ > should redirect output
			printf(">\n");
		stru->xpipe = stru->xpipe->next;
	}
	return;
}
