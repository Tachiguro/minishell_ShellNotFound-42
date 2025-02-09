#include "sh.h"

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
			str->exe = &ex;
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
	free(fullpath);
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
		ft_exit(str->vars->args, str);
		printf("Builtin exit called.\n");
	}
	else
	{
		/* If we got here, logic in is_built_in might differ. */
	}
	return (ret);
}

void convert_tree(t_tree *tree, t_exec_pipe **pipe)
{
    if (!tree)
        return;

    *pipe = malloc(sizeof(t_exec_pipe));
    if (!*pipe)
        return;

    (*pipe)->cmd = NULL;
	(*pipe)->args = NULL;
    (*pipe)->args = NULL;
    (*pipe)->re = NULL;
    (*pipe)->next = NULL;
	(*pipe)->redirectors = NULL;

    if (tree->type == T_WORD)
    {
        (*pipe)->cmd = ft_strdup(tree->args[0]);
        if (tree->args)
            (*pipe)->args = (char **)ft_array_dup((void **)tree->args, "char");

        if (tree->outfile)
        {
            if (tree->append)
                (*pipe)->re = ft_strdup(">>");
            else
                (*pipe)->re = ft_strdup(">");
        }
    }
    else if (tree->type == T_PIPE)
    {
        t_exec_pipe *left_pipe = NULL;
        t_exec_pipe *right_pipe = NULL;
        
        convert_tree(tree->left, &left_pipe);
        convert_tree(tree->right, &right_pipe);

        if (left_pipe)
        {
            t_exec_pipe *temp = left_pipe;
            while (temp->next)
                temp = temp->next;
            if (temp->re)
                free(temp->re);
            temp->re = ft_strdup("|");
            temp->next = right_pipe;
        }

        *pipe = left_pipe;
    }
}
// typedef struct s_execution
// {
// 	char	*candidate;
// 	char	*full_path;
// 	char	*path_env;
// 	char	**paths;
// 	char	*temp;
// }	t_exec;
void init_ex(t_str *str)
{
    t_exec *ex = malloc(sizeof(t_exec));
    if (!ex)
        return;

    ex->candidate = NULL;
    ex->full_path = NULL;
    ex->path_env = NULL;
    ex->paths = NULL;
    ex->temp = NULL;

    str->exe = ex;
}

void ex_lst(t_exec_pipe **pipe)
{
    *pipe = malloc(sizeof(t_exec_pipe));
    if (!*pipe)
        return;

    (*pipe)->cmd = strdup("exit");
    (*pipe)->args = malloc(sizeof(char *) * 2);
    if (!(*pipe)->args)
    {
        free((*pipe)->cmd);
        free(*pipe);
        return;
    }

    (*pipe)->args[0] = strdup("exit");
    (*pipe)->args[1] = NULL;
    (*pipe)->redirectors = NULL;
    (*pipe)->outfile = NULL;
    (*pipe)->new_out = NULL;
    (*pipe)->infile = NULL;
    (*pipe)->new_in = NULL;
    (*pipe)->next = NULL;
    (*pipe)->re = NULL;
}

int exe(t_tree *tree, bool ex)
{
	t_env  envi;
	t_vars vars;
	t_str  str;
	t_exec_pipe *pipe;

	printf("Reached execution");
	init_env(&envi);
	if (ex)
	{
		ex_lst(&pipe);
		init_ex(&str);
	}
	else
		convert_tree(tree, &pipe);
	str.environs = &envi;
	str.vars = &vars;
	str.xpipe = pipe;
	printf("Cmd is %s\n", pipe->cmd);
	if (is_built_in(pipe->cmd) == 1)
	{
		//printf("Not built in!\n");
		exec_intern(pipe->cmd, &str);
	}
	else
	{
		//printf("built in check\n");
		exec_external(pipe->cmd, &str, 1);
	}

	return (0);
}
