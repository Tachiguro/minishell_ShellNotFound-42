#include "sh.h"

/*
** ========================================================
**  find_executable_path
**    (Currently incomplete - just handles slash)
** ========================================================
*/
char *find_executable_path(char *cmd, t_str *str)
{
    t_exec *ex;
    int i;

    ex = malloc(sizeof(t_exec));
    if (!ex)
        return (NULL);

    i = 0;
    ex->candidate = NULL;

    if (contains_slash(cmd))
    {
        if (access(cmd, X_OK) == 0)
        {
            free(ex);
            return (ft_strdup(cmd));
        }
        free(ex);
        return (NULL);
    }

    ex->path_env = get_env_value("PATH=", str->environs->env);
    if (!ex->path_env)
    {
        free(ex);
        return (NULL);
    }

    ex->paths = ft_split(ex->path_env, ':');
    if (!ex->paths)
    {
        free(ex->path_env);
        free(ex);
        return (NULL);
    }

    while (ex->paths[i])
    {
        ex->temp = ft_strjoin(ex->paths[i], "/");
        ex->candidate = ft_strjoin(ex->temp, cmd);
        free(ex->temp);
        ex->temp = NULL;  // Prevent use-after-free

        if (access(ex->candidate, X_OK) == 0)
        {
            // Store in `str->exe` only when successful
            str->exe = ex;
            free(ex->path_env);
            ex->path_env = NULL;

            int j = 0;
            while (ex->paths[j])
            {
                free(ex->paths[j]);
                j++;
            }
            free(ex->paths);
            ex->paths = NULL;

            return (ex->candidate);
        }

        free(ex->candidate);  // Fix potential memory leak
        ex->candidate = NULL;
        i++;
    }

    // No valid path found, free everything
    free(ex->path_env);
    int j = 0;
    while (ex->paths[j])
    {
        free(ex->paths[j]);
        j++;
    }
    free(ex->paths);
    free(ex);

    return (NULL);
}




/*
** ========================================================
**  exec_external
** ========================================================
*/
int exec_external(char *cmd, t_str *str)
{
    char    *fullpath;
    int     status;
    pid_t   pid;

    fullpath = find_executable_path(cmd, str);
    if (!fullpath)
    {
        printf("minishell: command not found: %s\n", cmd);
        return (127);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        if (fullpath != str->exe->candidate) // Prevent double-free
            free(fullpath);
        return (1);
    }

    if (pid == 0) // Child Process
    {
        execve(fullpath, str->xpipe->args, str->environs->env);
        perror("execve");
        if (fullpath != str->exe->candidate)
            free(fullpath);
        exit(1);
    }
    else // Parent Process
    {
        waitpid(pid, &status, 0);
        if (fullpath != str->exe->candidate)
            free(fullpath);
        return (WEXITSTATUS(status));
    }
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
		/* return */
	}
	return (ret);
}

void convert_tree(t_tree *tree, t_exec_pipe **pipe)
{
    t_exec_pipe *left_pipe;
    t_exec_pipe *right_pipe;
    t_exec_pipe *temp;

    if (!tree)
        return;
    if (tree->type == T_WORD)
    {
        *pipe = malloc(sizeof(t_exec_pipe));
        if (!*pipe)
            return;

        (*pipe)->cmd = ft_strdup(tree->args[0]);
        if (tree->outfile)
            (*pipe)->outfile = ft_strdup(tree->outfile);
        else
            (*pipe)->outfile = NULL;
        if (tree->infile)
            (*pipe)->infile = ft_strdup(tree->infile);
        else
            (*pipe)->infile = NULL;
        if (tree->args)
            (*pipe)->args = (char **)ft_array_dup((void **)tree->args, "char");
        else
            (*pipe)->args = NULL;
        if (tree->outfile)
        {
            if (tree->append)
            {
                (*pipe)->re = ft_strdup(">>");
                (*pipe)->append = 1;
            }
            else
            {
                (*pipe)->re = ft_strdup(">");
                (*pipe)->append = 0;
            }
        }
        else
            (*pipe)->re = NULL;
        
        (*pipe)->next = NULL;
        (*pipe)->redirectors = NULL;
    }
    else if (tree->type == T_PIPE)
    {
        right_pipe = NULL;
        left_pipe = NULL;
        convert_tree(tree->left, &left_pipe);
        convert_tree(tree->right, &right_pipe);
        
        if (left_pipe)
        {
            temp = left_pipe;
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
    if (str->exe)
        return;

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
    if (!(*pipe)->cmd)
    {
        free(*pipe);
        *pipe = NULL;
        return;
    }

    (*pipe)->args = malloc(sizeof(char *) * 2);
    if (!(*pipe)->args)
    {
        free((*pipe)->cmd);
        free(*pipe);
        *pipe = NULL;
        return;
    }

    (*pipe)->args[0] = strdup("exit");
    if (!(*pipe)->args[0])
    {
        free((*pipe)->args);
        free((*pipe)->cmd);
        free(*pipe);
        *pipe = NULL;
        return;
    }

    (*pipe)->args[1] = NULL;
    (*pipe)->redirectors = NULL;
    (*pipe)->outfile = NULL;
    (*pipe)->new_out = NULL;
    (*pipe)->infile = NULL;
    (*pipe)->new_in = NULL;
    (*pipe)->next = NULL;
    (*pipe)->re = NULL;
}

int exe(t_tree *tree, bool ex, t_token *token)
{
    t_env       *envi;
    t_vars      vars;
    t_str       str;
    t_exec_pipe *pipe = NULL;

    printf("Reached execution\n");

    envi = malloc(sizeof(t_env));
    if (!envi)
        return (1);
    init_env(envi);

    /* Setup the execution structure */
    str.parent_pid = getpid();
    str.tokens     = token;
    str.tree       = tree;
    str.environs   = envi;
    str.vars       = &vars;
    str.xpipe      = pipe;
    str.exe        = NULL;

    if (ex)
    {
        /* For exit command, build a minimal exec pipe */
        ex_lst(&pipe);
        if (!pipe)
        {
            free(envi);
            return (1);
        }
        init_ex(&str);
    }
    else
    {
        convert_tree(tree, &pipe);
    }
    str.xpipe = pipe;

    if (!pipe || !pipe->cmd)
    {
        cleanup(&str);
        return (1);
    }

    printf("Cmd is %s\n", pipe->cmd);

    /* execute entire pipeline */
    if (pipe->next)
    {
        exec_pipeline(&str);
    }
    else
    {
        /* Single command */
        if (is_built_in(pipe->cmd) == 1)
            exec_intern(pipe->cmd, &str);
        else
            exec_external(pipe->cmd, &str);
    }
    cleanup(&str);
    if (ex)
        exit(0);

    return (0);
}

