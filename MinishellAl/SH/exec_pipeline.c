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

	fullpath = find_executable_path(cmd_node->cmd, str);
	if (!fullpath)
	{
		fprintf(stderr, "minishell: command not found: %s\n", cmd_node->cmd);
		exit(127); // Common exit code for command not found
	}
	execve(fullpath, cmd_node->args, str->environs->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void handle_error(t_str *stru, const char *msg)
{
    perror(msg);
    cleanup(stru);
    exit(EXIT_FAILURE);
}

/*
 * child_intermediate - Handles an intermediate pipeline segment in the child.
 *
 * This function duplicates the previous pipe (if available) onto STDIN and the
 * current pipe's write end onto STDOUT, then executes the command. On any error,
 * it calls handle_error.
 */
static void child_intermediate(t_str *stru, t_exec_pipe *current,
    int *prev_fd_in, int pipefd[2])
{
    if (*prev_fd_in != -1)
    {
        if (dup2(*prev_fd_in, STDIN_FILENO) < 0)
        {
            handle_error(stru, "dup2");
        }
        close(*prev_fd_in);
    }
    if (pipefd[1] != -1)
    {
        if (dup2(pipefd[1], STDOUT_FILENO) < 0)
        {
            handle_error(stru, "dup2");
        }
        close(pipefd[0]);
        close(pipefd[1]);
    }
    exec_command(current, stru);
    handle_error(stru, "execve");
}


/*
 * parent process for an intermediate pipeline segment
 *
 * closes current pipe write end and the previous pipe
 * read end , then updates the previous pipe read end with the current pipe read end
 */
static void parent_intermediate(int *prev_fd_in, int pipefd[2])
{
    if (pipefd[1] != -1)
    {
        close(pipefd[1]);
    }
    if (*prev_fd_in != -1)
    {
        close(*prev_fd_in);
    }
    *prev_fd_in = pipefd[0];
}

/*
 * Forks and processes one intermediate pipeline segment.
 *
 * forks a new process and calls child_intermediate in the child while
 * the parent calls parent_intermediate on fork error, clean and exit.
 */
static void handle_intermediate_segment(t_str *stru, t_exec_pipe *current,
    int *prev_fd_in, int pipefd[2])
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        cleanup(stru);
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
        child_intermediate(stru, current, prev_fd_in, pipefd);
    else
        parent_intermediate(prev_fd_in, pipefd);
}

/*
 * Processes all intermediate pipeline nodes.
 *
 * loops through pipeline nodes whose re field equals "|". For each,
 * it sets up a pipe (if there is a next node) and calls handle_intermediate_segment.
 * It returns the node for the final command.
 */
static void process_in_helper(t_exec_pipe *current, int pipefd[2], t_str *stru)
{
    if (current->next)
    {
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
}
static t_exec_pipe *process_intermediates(t_str *stru, int *prev_fd_in)
{
    t_exec_pipe *current;
    int pipefd[2];

    current = stru->xpipe;
    while (current != NULL && current->re != NULL && 
           !ft_strcmp(current->re, "|"))
    {
        process_in_helper(current, pipefd, stru);
        handle_intermediate_segment(stru, current, prev_fd_in, pipefd);
        current = current->next;
        if (current != NULL && current->re != NULL && 
            ft_strcmp(current->re, "|") != 0)
            break;
    }
    return current;
}

/*
 *Sets up output redirection in the final command.
 *
 * sets output flags (using O_APPEND if needed) and redirects
 * STDOUT to the opened outfile.
 */
static void output_re_helper(int *filed)
{
    int fd;

    fd = *filed;
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
}

static void handle_output_redirection(t_exec_pipe *current)
{
    int fd;
    int flags;

    flags = O_WRONLY;
    if (current->append)
    {
        flags |= O_CREAT;
        flags |= O_APPEND;
    }
    else
    {
        flags |= O_CREAT;
        flags |= O_TRUNC;
    }
    fd = open(current->outfile, flags, 0644);
    output_re_helper(&fd);
    close(fd);
}

/*
 * Processes final pipeline command in the child.
 *
 * In the child process for the final command, this function duplicates the previous
 * pipe to STDIN (if available), handles output redirection if outfile is set,
 * and executes the command.
 */
static void final_child(t_str *stru, int prev_fd_in, t_exec_pipe *current)
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
        handle_output_redirection(current);
    }
    exec_command(current, stru);
    perror("execve");
    exit(EXIT_FAILURE);
}

/*
 * process_final_command - Processes the final command in the pipeline.
 *
 * This function forks a child for the final command. In the child, it calls
 * final_child; in the parent, it closes any remaining file descriptor and waits.
 */
static void process_final_command(t_str *stru, int prev_fd_in, t_exec_pipe *current)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        final_child(stru, prev_fd_in, current);
    }
    else
    {
        if (prev_fd_in != -1)
        {
            close(prev_fd_in);
        }
        waitpid(pid, &status, 0);
    }
}

/*
 * exec_pipe - Executes a pipeline of commands.
 *
 * This function processes intermediate pipeline nodes and then the final command.
 * It then waits for all intermediate children to finish.
 */
static void exec_pipe(t_str *stru)
{
    t_exec_pipe *current;
    int prev_fd_in;
    int status;

    prev_fd_in = -1;
    current = process_intermediates(stru, &prev_fd_in);
    if (current != NULL)
        process_final_command(stru, prev_fd_in, current);
    current = stru->xpipe;
    while (current != NULL && current->re != NULL &&
           !ft_strcmp(current->re, "|"))
    {
        wait(&status);
        current = current->next;
    }
}

///////////////////////////
// > (Output Redirection):
// Redirects the standard output (stdout) of a command to a file, overwriting the file if it already exists.
// static void re_out(t_str *stru)

/*
 * re_out_child - In the child process, redirects STDOUT to the given file descriptor
 * and executes the command.
 */
static void re_out_child(t_str *stru, int fd)
{
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(1);
    }
    close(fd);
    execve(stru->xpipe->cmd, stru->xpipe->args, stru->environs->env);
    perror("execve");
    exit(1);
}

/*
 * re_out - Handles output redirection for '>' and '>>'.
 *
 * This function sets the appropriate flags based on whether append is set,
 * opens the outfile, forks a child process, and calls re_out_child in the child.
 * The parent process closes the file descriptor and waits for the child.
 */
static void re_out_helper(pid_t   pid,int fd, t_str *stru)
{
    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return;
    }
    if (pid == 0)
        re_out_child(stru, fd);
    else
    {
        close(fd);
        waitpid(pid, NULL, 0);
    }
}

static void re_out(t_str *stru)
{
    pid_t   pid;
    int     fd;
    int     flags;
    char   *outfile;

    outfile = stru->xpipe->outfile;
    printf("REACHED RE OUT !!!!\n");
    if (stru->xpipe->append)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    fd = open(outfile, flags, 0644);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    pid = fork();
    re_out_helper(pid, pid, stru);
}


/*
 * re_in_child - Executes the command for input redirection in the child process.
 *
 * This function duplicates the file descriptor to STDIN, closes the original fd,
 * and then calls execve with the command and its arguments. If any error occurs,
 * it prints an error message and exits.
 */
static void re_in_child(t_str *stru, int fd)
{
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    execve(stru->xpipe->cmd, stru->xpipe->args, stru->environs->env);
    perror("execve");
    exit(EXIT_FAILURE);
}

/*
 * re_in - Handles input redirection for commands using '<' or '<<'.
 *
 * This function opens the infile specified in the execution pipeline, forks a child,
 * and in the child process calls re_in_child. The parent process waits for the child.
 */
static void re_in_helper(t_str *stru, pid_t pid, int fd)
{
    if (pid == 0)
        re_in_child(stru, fd);
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
    re_in_helper(stru, pid, fd);
}

void exec_pipeline(t_str *stru)
{
    t_exec_pipe *head;
    t_exec_pipe *current;

    head = stru->xpipe;
    current = head;
    while (current)
    {
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
