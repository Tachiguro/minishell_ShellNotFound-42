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

#include "sh.h"

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

static void exec_pipe(t_str *stru)
{
    t_exec_pipe *current;
    int pipefd[2];
    int prev_fd_in;
    pid_t pid;
    int status;

    prev_fd_in = -1;
    current = stru->xpipe;

    while (current != NULL && !ft_strcmp(current->re, "|"))
    {
        if (current->next)
        {
            printf("NEXT CMD FOUND it is %s !!!\n", current->next->cmd);
            if (pipe(pipefd) < 0)
            {
                perror("pipe");
                cleanup(stru);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            pipefd[0] = -1;
            pipefd[1] = -1;
        }
        pid = fork();
        printf("here1 !!!\n");
        if (pid < 0)
        {
            perror("fork");
            cleanup(stru);
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if (prev_fd_in != -1)
            {
                if (dup2(prev_fd_in, STDIN_FILENO) < 0)
                {
                    perror("dup2");
                    cleanup(stru);
                    exit(EXIT_FAILURE);
                }
                close(prev_fd_in);
            }
            if (pipefd[1] != -1)
            {
                if (dup2(pipefd[1], STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    cleanup(stru);
                    exit(EXIT_FAILURE);
                }
                close(pipefd[0]);
                close(pipefd[1]);
            }
            printf("CHILD EXECUTE!!!!\n");
            exec_command(current, stru);
            perror("execve");
            cleanup(stru);
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("here2 !!!\n");
            if (pipefd[1] != -1)
                close(pipefd[1]);
            if (prev_fd_in != -1)
                close(prev_fd_in);
            prev_fd_in = pipefd[0];
        }
        current = current->next;
        while (current != NULL && current->re && ft_strcmp(current->re, "|"))
        {
            printf("NO MORE PIPE FOUND!!!\n");
            break;
        }
    }
    if (current != NULL)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if (prev_fd_in != -1)
            {
                if (dup2(prev_fd_in, STDIN_FILENO) < 0)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(prev_fd_in);
            }
            if (current->outfile != NULL)
            {
                int fd;
                int flags;

                flags = O_WRONLY;
                if (current->append)
                {
                    flags = flags | O_CREAT;
                    flags = flags | O_APPEND;
                }
                else
                {
                    flags = flags | O_CREAT;
                    flags = flags | O_TRUNC;
                }
                fd = open(current->outfile, flags, 0644);
                if (fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }
                close(fd);
            }
            exec_command(current, stru);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else
        {
            if (prev_fd_in != -1)
                close(prev_fd_in);
            waitpid(pid, &status, 0);
        }
    }
    current = stru->xpipe;
    while (current != NULL && current->re && !ft_strcmp(current->re, "|"))
    {
        wait(&status);
        current = current->next;
    }
}



// > (Output Redirection):
// Redirects the standard output (stdout) of a command to a file, overwriting the file if it already exists.
// Example:

static void re_out(t_str *stru)
{
    pid_t   pid;
    int     fd;
    int     flags;
    char   *outfile;

    outfile = stru->xpipe->outfile;
	printf("REACHED RE OUT !!!!\n");
    if (stru->xpipe->append)
    {
        flags = O_WRONLY;
        flags = flags | O_CREAT;
        flags = flags | O_APPEND;
    }
    else
    {
        flags = O_WRONLY;
        flags = flags | O_CREAT;
        flags = flags | O_TRUNC;
    }
    fd = open(outfile, flags, 0644);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return;
    }

    if (pid == 0)  /* Child process */
    {
        /* Redirect STDOUT to the file descriptor */
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("dup2");
            close(fd);
            exit(1);
        }
        close(fd);
        /* Execute the command; stru->xpipe->cmd holds the command, 
           and stru->xpipe->args holds the arguments; 
           stru->environs->env holds the environment variables */
        execve(stru->xpipe->cmd, stru->xpipe->args, stru->environs->env);
        perror("execve");
        exit(1);
    }
    else
    {
        close(fd);
        waitpid(pid, NULL, 0);
    }
}

static void re_in(t_str *stru)
{
    pid_t pid;
    int fd;
    char *infile;

    infile = stru->xpipe->infile;
    printf("REACHED RE IN !!!!\n");

    fd = open(infile, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return;
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return;
    }

    if (pid == 0)  /* Child process */
    {
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            perror("dup2");
            close(fd);
            exit (EXIT_FAILURE);
        }
        close(fd);

        execve(stru->xpipe->cmd, stru->xpipe->args, stru->environs->env);
        perror("execve");
        exit (EXIT_FAILURE);
    }
    else  /* Parent process */
    {
        close(fd);
        waitpid(pid, NULL, 0);
    }
}

void exec_pipeline(t_str *stru)
{
    t_exec_pipe *head;
    t_exec_pipe *current;

    head = stru->xpipe;
    current = head;
    while (current)
    {
        /* 
         * Before executing a segment, set stru->xpipe to the current node.
         * This is needed because exec_pipe and re_out use stru->xpipe.
         */
        stru->xpipe = current;
        if ((current->next) && (ft_strcmp(current->re, "|") == 0))
            exec_pipe(stru);
        else if ((current->next) && (ft_strcmp(current->re, "<<") == 0))
            re_in(stru);
        else if ((current->next) && (ft_strcmp(current->re, ">>") == 0))
            re_out(stru);
        else if ((current->next) && (ft_strcmp(current->re, "<") == 0))
            re_in(stru);
        else if ((current->next) && (ft_strcmp(current->re, ">") == 0))
            re_out(stru);
        current = current->next;
    }
    stru->xpipe = head;
}


