#include "minishell.h"
#include "../libft/libft.h"

/*
** ========================================================
**  find_executable_path
**    (Currently incomplete - just handles slash)
** ========================================================
*/
char *find_executable_path(char *cmd, t_str *str)
{
	t_exec ex;
	int i;

	i = 0;
	if (contains_slash(cmd))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	/* If no slash, we’d normally search PATH from str->environs->env. */
	ex.path_env = get_env_value("PATH=", str->environs->env);
	if (!ex.path_env)
		return (NULL);
	ex.paths = ft_split(ex.path_env, ':');
	if (!ex.paths)
		return (NULL);
	while (ex.paths[i])
	{
		ex.temp = ft_strjoin(ex.paths[i], "/"); //Suppose paths[i] = "/usr/bin". Now temp = "/usr/bin/".
		if(!ex.temp)
		{
			printf("failed strjoin");
			return (NULL);//error strjoin failed, free memory here
		}
		ex.candidate = ft_strjoin(ex.temp, cmd);
		if (access(ex.candidate, X_OK) == 0)
		{
			str->exe = &ex;
			printf("found cmd!!!! in %s\n", ex.candidate); //Debug
			return(ex.candidate);
		}
		i++;
	}
	/* Return NULL to indicate not found for now. */
	return (NULL);
}

/*
** ========================================================
**  exec_external
** ========================================================
*/
int exec_external(char *cmd, t_str *str, bool start)
{
	char	*fullpath;
	int		status;
	pid_t	pid;

	fullpath = find_executable_path(cmd, str);
	if (check_redirect(str) && start)
		exec_pipeline(str);
	else
	{
		printf("Redirectors empty!!!!!!!!! \n");
		if (!fullpath)
		{
			printf("minishell: command not found: %s\n", cmd);
			return (127);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			free(fullpath);
			return (1);
		}
		if (pid == 0)
		{
			/* Child */
			execve(fullpath, str->xpipe->args, str->environs->env);
			perror("execve");
			free(fullpath);
			exit(1);
		}
		else
		{
			/* Parent */
			waitpid(pid, &status, 0);
			free(fullpath);
			return (WEXITSTATUS(status));
		}
	}
	return(0);
}

/*
** ========================================================
**  exec_intern (Builtins)
** ========================================================
*/
int exec_intern(char *cmd, t_str *str)
{
	int ret;

	ret = 0;
	if(!str)
		ret = 0;
	if (!ft_strcmp(cmd, "echo"))
	{
		// For demonstration, assume you have a function ft_echo(...)
		// that uses str->vars->args for the arguments
		//ft_echo(cmd, str->vars->args[0]);
		printf("Builtin echo called.\n");
	}
	else if (!ft_strcmp(cmd, "cd"))
	{
		//ft_cd(str->vars->args[0]);
		printf("Builtin cd called.\n");
	}
	else if (!ft_strcmp(cmd, "pwd"))
	{
		//ft_pwd();
		printf("Builtin pwd called.\n");
	}
	else if (!ft_strcmp(cmd, "export"))
	{
		printf("Builtin export called.\n");
	}
	else if (!ft_strcmp(cmd, "unset"))
	{
		//ft_unset(str->vars->args[0]);
		printf("Builtin unset called.\n");
	}
	else if (!ft_strcmp(cmd, "env"))
	{
		//ft_env()
		printf("Builtin env called.\n");
	}
	else if (!ft_strcmp(cmd, "exit"))
	{
		//ft_exit(str->vars->args);
		printf("Builtin exit called.\n");
	}
	else
	{
		/* If we got here, logic in is_built_in might differ. */
	}
	return (ret);
}

/*
** ========================================================
** test main
** ========================================================
*/

// typedef struct s_xlist //execution list fill me in tokenization
// {
// 	char			**redirectors;
// 	char			*outfile;
// 	char			*new_out;
// 	char			*infile;
// 	char			*new_in;
// 	char			**flags;
// 	char			**args;
// 	void			*next;
// 	char			*cmd;
// 	char			*sign;
// }	t_exec_pipe;

void set_lst(t_exec_pipe *pipe)
{
    t_exec_pipe *current = pipe;
    t_exec_pipe *next_node;

    // Initialize the first node
    current->cmd = strdup("ls"); // Dynamically duplicate "ls"

    // Allocate and initialize args
    current->args = malloc(sizeof(char *) * 2); // Space for 3 arguments
    current->args[0] = strdup("ls");           // First argument
	current->cmd = ft_strdup("ls");
    current->args[1] = NULL;                   // Null-terminate the args array

    // Allocate and initialize flags
    current->flags = malloc(sizeof(char *) * 1); // Space for 1 flag
    current->flags[0] = NULL;                    // No flags

    // Allocate and initialize re
    current->re = strdup("|"); // String for the pipe character

    // Allocate and initialize the next node
    current->next = malloc(sizeof(t_exec_pipe));
	next_node = current->next;
    next_node->cmd = strdup("grep"); // Command for the second node
    next_node->args = malloc(sizeof(char *) * 2); // Space for 3 arguments
    next_node->args[0] = strdup("grep");         // First argument
    next_node->args[1] = "en";
	next_node->args[2] = NULL;                   // Null-terminate the args array
    // Allocate and initialize flags
    next_node->flags = malloc(sizeof(char *) * 1); // Space for 1 flag
    next_node->flags[0] = NULL;                    // No flags
    // Allocate and initialize re
    next_node->re = strdup(""); // String for the semicolon
    next_node->next = NULL; // Terminate the list
}

int main(void)
{
	t_env  envi;
	t_vars vars;
	t_str  str;
	t_exec_pipe pipe;
	char  *cmd;

	/* 1) Initialize environment */
	init_env(&envi);
	// fill list for debug
	set_lst(&pipe);

	/* 3) Setup 'str' */
	str.environs = &envi;
	str.vars = &vars;
	pipe.redirectors = malloc(sizeof(char *) * (1 + 1));
	pipe.redirectors[0] = malloc(sizeof(char) * (1 + 1));
	pipe.redirectors[1] = malloc(sizeof(char) * (1 + 1));
	pipe.redirectors[0][0] = '|';
	pipe.redirectors[1] = NULL;
	// printf("EXEC PIPELINE REACHED!!!!!!!!\n");
	// exit(0);
	str.xpipe = &pipe;
	// printf("HERE!!!!\n");
	// exit(0);

	/* 4) Choose a command to run.
	**    For demonstration, let's do "echo".
	*/
	cmd = "ls";
	printf("Cmd is %s\n", cmd);

	/* 5) Check if builtin or external */
	//printf("before built in check\n");
	if (is_built_in(cmd) == 1)
	{
		//printf("Not built in!\n");
		exec_intern(cmd, &str);
	}
	else
	{
		//printf("built in check\n");
		exec_external(cmd, &str, 1);
	}

	return (0);
}
