#include "sh.h"

/*typedef struct s_xlist //execution list fill me in tokenization
{
	char			**redirectors;
	char			*outfile;
	char			*new_out;
	char			*infile;
	char			*new_in;
	char			**args;
	struct s_xlist	*next;
	char			*cmd;
	char			*re;
}	t_exec_pipe;*/

// typedef struct s_execution
// {
// 	char	*candidate;
// 	char	*full_path;
// 	char	*path_env;
// 	char	**paths;
// 	char	*temp;
// }	t_exec;

// typedef struct s_environ
// {
// 	char	**env;

// }	t_env;
void clean_environ(t_env *env)
{
    int i;

    if (!env || !env->env)
        return;

    i = 0;
    while (env->env[i])
    {
        free(env->env[i]);
        i++;
    }
    free(env->env);
    free(env);  
}


void clean_exec(t_exec *exe)
{
    int i;

    if (!exe)
        return;

    printf("DEBUG: Freeing exe->candidate = %p\n", exe->candidate);
    if (exe->candidate)
    {
        free(exe->candidate);
        exe->candidate = NULL;
    }

    printf("DEBUG: Freeing exe->full_path = %p\n", exe->full_path);
    // if (exe->full_path)
    // {
    //     free(exe->full_path);
    //     exe->full_path = NULL;
    // }

    printf("DEBUG: Freeing exe->path_env = %p\n", exe->path_env);
    if (exe->path_env)
    {
        free(exe->path_env);
        exe->path_env = NULL;
    }

    if (exe->paths)
    {
        i = 0;
        while (exe->paths[i])
        {
            printf("DEBUG: Freeing exe->paths[%d] = %p\n", i, exe->paths[i]);
            free(exe->paths[i]);
            exe->paths[i] = NULL;
            i++;
        }
        printf("DEBUG: Freeing exe->paths = %p\n", exe->paths);
        free(exe->paths);
        exe->paths = NULL;
    }

    printf("DEBUG: Freeing exe->temp = %p\n", exe->temp);
    if (exe->temp)
    {
        free(exe->temp);
        exe->temp = NULL;
    }

    printf("DEBUG: Freeing exe struct = %p\n", exe);
    free(exe);
}

void clean_lst(t_exec_pipe *xpipe)
{
    int i;

    if (!xpipe)
        return;
    if (xpipe->redirectors)
    {
        i = 0;
        while (xpipe->redirectors[i])
        {
            free(xpipe->redirectors[i]);
            xpipe->redirectors[i] = NULL;  // Prevent double free
            i++;
        }
        free(xpipe->redirectors);
        xpipe->redirectors = NULL;
    }
    if (xpipe->args)
    {
        i = 0;
        while (xpipe->args[i])
        {
            free(xpipe->args[i]);
            xpipe->args[i] = NULL;
            i++;
        }
        free(xpipe->args);
        xpipe->args = NULL;
    }
    if (xpipe->cmd)
    {
        free(xpipe->cmd);
        xpipe->cmd = NULL;
    }
    if (xpipe->re)
    {
        free(xpipe->re);
        xpipe->re = NULL;
    }
    if (xpipe->outfile)
    {
        free(xpipe->outfile);
        xpipe->outfile = NULL;
    }
    if (xpipe->infile)
    {
        free(xpipe->infile);
        xpipe->infile = NULL;
    }
   
    if (xpipe->next)
    {
        clean_lst(xpipe->next);
        xpipe->next = NULL;
    }
    free(xpipe);
}



void cleanup(t_str *stru)
{
    printf("DEBUG: getpid() = %d, stru->parent_pid = %d\n", getpid(), stru->parent_pid);
    if (getpid() != stru->parent_pid)
    {
        printf("DEBUG: Skipping cleanup due to PID mismatch.\n");
        return;  // Only parent should run cleanup
    }

    printf("reached cleanup\n");

    if (stru->xpipe)
        clean_lst(stru->xpipe);
    stru->xpipe = NULL;

    if (stru->exe)
    {
        clean_exec(stru->exe);
        stru->exe = NULL;
    }

    if (stru->environs)
    {
        clean_environ(stru->environs);
        stru->environs = NULL;
    }

    if (stru->tree)
    {
        free_tree(stru->tree);
        stru->tree = NULL;
    }
    printf("DEBUG: stru->tokens = %p\n", (void *)stru->tokens);
    if (stru->tokens)
    {
        free_tokens(stru->tokens);
        stru->tokens = NULL;
    }
}
