#include "sh.h"

void	convert_tree(t_tree *tree, t_exec_pipe **pipe);

/*
** ========================================================
**  find_executable_path
**    (Currently incomplete - just handles slash)
** ========================================================
*/
// char *find_executable_path(char *cmd, t_str *str)
// {
//     t_exec *ex;
//     int i;
//     int j;

//     ex = malloc(sizeof(t_exec));
//     if (!ex)
//         return (NULL);

//     i = 0;
//     ex->candidate = NULL;
//     if (contains_slash(cmd))
//     {
//         if (access(cmd, X_OK) == 0)
//         {
//             free(ex);
//             return (ft_strdup(cmd));
//         }
//         free(ex);
//         return (NULL);
//     }
//     ex->path_env = get_env_value("PATH=", str->environs->env);
//     if (!ex->path_env)
//     {
//         free(ex);
//         return (NULL);
//     }
//     ex->paths = ft_split(ex->path_env, ':');
//     if (!ex->paths)
//     {
//         free(ex->path_env);
//         free(ex);
//         return (NULL);
//     }
//     while (ex->paths[i])
//     {
//         ex->temp = ft_strjoin(ex->paths[i], "/");
//         ex->candidate = ft_strjoin(ex->temp, cmd);
//         free(ex->temp);
//         ex->temp = NULL;  // Prevent use-after-free
//         if (access(ex->candidate, X_OK) == 0)
//         {
//             // Store in `str->exe` only when successful
//             str->exe = ex;
//             free(ex->path_env);
//             ex->path_env = NULL;
//             int j = 0;
//             while (ex->paths[j])
//             {
//                 free(ex->paths[j]);
//                 j++;
//             }
//             free(ex->paths);
//             ex->paths = NULL;

//             return (ex->candidate);
//         }

//         free(ex->candidate);  // Fix potential memory leak
//         ex->candidate = NULL;
//         i++;
//     }
//     // No valid path found, free everything
//     free(ex->path_env);
//     j = 0;
//     while (ex->paths[j])
//     {
//         free(ex->paths[j]);
//         j++;
//     }
//     free(ex->paths);
//     free(ex);
//     return (NULL);
// }

/*
 * init_exec_struct - Allocates and initializes a t_exec structure.
 *
 * This function allocates a new t_exec, retrieves the PATH variable from the
 * environment, and splits it by ':' into an array of directories.
 * Returns the allocated structure or NULL on error.
 */
static t_exec *init_exec_struct(t_str *str)
{
    t_exec *ex;

    ex = malloc(sizeof(t_exec));
    if (!ex)
        return (NULL);
    ex->candidate = NULL;
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
    return (ex);
}

/*
 * free_paths_array - Frees the array of directory strings in t_exec.
 *
 * This function iterates through ex->paths, frees each directory string,
 * and then frees the paths array itself.
 */
static void free_paths_array(t_exec *ex)
{
    int j = 0;

    while (ex->paths[j])
    {
        free(ex->paths[j]);
        j++;
    }
    free(ex->paths);
}

/*
 * try_executable - Searches through ex->paths for an executable command.
 *
 * For each directory in ex->paths, this function constructs a candidate by
 * concatenating the directory, "/" and cmd, then checks if the candidate is executable.
 * If found, it frees unneeded memory and returns the candidate path.
 */
static char *try_executable(t_exec *ex, char *cmd, t_str *str)
{
    int i = 0;
    char *candidate;

    while (ex->paths[i])
    {
        ex->temp = ft_strjoin(ex->paths[i], "/");
        candidate = ft_strjoin(ex->temp, cmd);
        free(ex->temp);
        ex->temp = NULL;
        if (access(candidate, X_OK) == 0)
        {
            str->exe = ex;
            free(ex->path_env);
            ex->path_env = NULL;
            free_paths_array(ex);
            ex->paths = NULL;
            return (candidate);
        }
        free(candidate);
        i++;
    }
    return (NULL);
}

/*
 * find_executable_path - Finds the full path to an executable command.
 *
 * If cmd contains a '/', it checks it directly. Otherwise, it initializes a
 * t_exec structure using the PATH variable and searches through each directory.
 * Returns the full path if found, or NULL if no valid path is found.
 */
char *find_executable_path(char *cmd, t_str *str)
{
    t_exec *ex;
    char *candidate;

    if (contains_slash(cmd))
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    ex = init_exec_struct(str);
    if (!ex)
        return (NULL);
    candidate = try_executable(ex, cmd, str);
    if (candidate)
        return (candidate);
    free(ex->path_env);
    ex->path_env = NULL;
    free_paths_array(ex);
    free(ex);
    return (NULL);
}


int exec_external_helper(t_str *str, pid_t   pid, char *fullpath)
{
    int     status;


    status = 0;
    if (pid == 0)
    {
        execve(fullpath, str->xpipe->args, str->environs->env);
        perror("execve");
        if (fullpath != str->exe->candidate)
            free(fullpath);
        exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (fullpath != str->exe->candidate)
            free(fullpath);
        return (WEXITSTATUS(status));
    }
}

/*
** ========================================================
**  exec_external
** ========================================================
*/
int exec_external(char *cmd, t_str *str)
{
    char    *fullpath;
    pid_t   pid;
    int ret;

    ret = 0;
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
        if (fullpath != str->exe->candidate)
            free(fullpath);
        return (1);
    }
    ret = exec_external_helper(str, pid, fullpath);
    return(ret);
}

void exec_intern_helper(char *cmd, t_str *str)
{
    if (!ft_strcmp(cmd, "export"))
        ft_export(cmd, str);
	else if (!ft_strcmp(cmd, "unset"))
	{
        if (str->xpipe->args[1])
		    ft_unset(str->xpipe->args[1], str->environs);
	}
	else if (!ft_strcmp(cmd, "env"))
		ft_env();
	else if (!ft_strcmp(cmd, "exit"))
	{
		ft_exit(str->vars->args, str);
		printf("Builtin exit called.\n");
	}
}

/*
** ========================================================
**  exec_intern (Builtins)
** ========================================================
*/
void exec_intern(char *cmd, t_str *str)
{
	if (!ft_strcmp(cmd, "echo"))
	{
        if (str->xpipe->args[1])
        {
            if (str->xpipe->args[2] && !ft_strcmp(str->xpipe->args[2], "-n"))
                ft_echo(str->xpipe->args[1], "-n");
            else
                ft_echo(str->xpipe->args[1], "XXX");
        }
        else
            ft_echo("\n", "XXX");
	}
	else if (!ft_strcmp(cmd, "cd"))
        ft_cd(str->xpipe->args[1]);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
    else
        exec_intern_helper(cmd, str);
}

/*
 * convert_word - Converts a T_WORD tree node into an execution pipeline node.
 *
 * This function allocates a new t_exec_pipe node, duplicates the command,
 * infile, outfile, and arguments from the tree node, and sets the redirection
 * type based on whether tree->outfile is set and tree->append is true.
 */
static void	convert_word_helper(t_tree *tree, t_exec_pipe **pipe)
{
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

static void	convert_word(t_tree *tree, t_exec_pipe **pipe)
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
    convert_word_helper(tree, pipe);
}

/*
 * convert_pipe - Converts a T_PIPE tree node into an execution pipeline.
 *
 * This function recursively converts the left and right subtrees,
 * then appends the right pipeline to the end of the left pipeline by
 * replacing the final redirection with "|" and linking the nodes.
 */
static void	convert_pipe(t_tree *tree, t_exec_pipe **pipe)
{
	t_exec_pipe	*left_pipe;
	t_exec_pipe	*right_pipe;
	t_exec_pipe	*temp;

	left_pipe = NULL;
	right_pipe = NULL;
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

void	convert_tree(t_tree *tree, t_exec_pipe **pipe)
{
	if (!tree)
		return;
	if (tree->type == T_WORD)
		convert_word(tree, pipe);
	else if (tree->type == T_PIPE)
		convert_pipe(tree, pipe);
}

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

void init_ex_lst2(t_exec_pipe **pipe)
{
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

void init_ex_lst(t_exec_pipe **pipe)
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
    init_ex_lst2(pipe);
}

int exe_helper(bool ex, t_str *str)
{

    if (!str->xpipe || !str->xpipe->cmd)
    {
        cleanup(str);
        return (1);
    }
    if (str->xpipe->next)
        exec_pipeline(str);
    else
    {
        if (is_built_in(str->xpipe->cmd) == 1)
            exec_intern(str->xpipe->cmd, str);
        else
            exec_external(str->xpipe->cmd, str);
    }
    cleanup(str);
    if (ex)
        exit(0);
    return(0);
}

static int init_common_structure(t_str *str, t_tree *tree, t_token *token, t_vars *vars)
{
    t_env *envi;

    envi = malloc(sizeof(t_env));
    if (!envi)
        return (1);
    init_env(envi);
    str->parent_pid = getpid();
    str->tokens = token;
    str->tree = tree;
    str->environs = envi;
    str->vars = vars;
    str->exe = NULL;
    return (0);
}

static int init_pipe_structure(t_str *str, bool ex)
{
    t_exec_pipe *pipe;

    pipe = NULL;
    if (ex)
    {
        init_ex_lst(&pipe);
        if (!pipe)
            return (1);
        init_ex(str);
    }
    else
        convert_tree(str->tree, &pipe);
    str->xpipe = pipe;
    return (0);
}

int exe(t_tree *tree, bool ex, t_token *token)
{
    t_vars vars;
    t_str  str;

    if (init_common_structure(&str, tree, token, &vars))
        return (1);
    if (init_pipe_structure(&str, ex))
    {
        free(str.environs);
        return (1);
    }
    exe_helper(ex, &str);
    return (0);
}
