#include "sh.h"

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

void clean_exec_helper(t_exec *exe, int *i)
{
    if (exe->paths)
    {
        i = 0;
        while (exe->paths[*i])
        {
            free(exe->paths[*i]);
            exe->paths[*i] = NULL;
            i++;
        }
        free(exe->paths);
        exe->paths = NULL;
    }
    if (exe->temp)
    {
        free(exe->temp);
        exe->temp = NULL;
    }
}

void clean_exec(t_exec *exe)
{
    int i;

    if (!exe)
        return;
    if (exe->candidate)
    {
        free(exe->candidate);
        exe->candidate = NULL;
    }
    if (exe->path_env)
    {
        free(exe->path_env);
        exe->path_env = NULL;
    }
    clean_exec_helper(exe, &i);
    free(exe);
}

static void clean_lst_helper(t_exec_pipe *xpipe, int *i)
{
    *i = 0;
    if (xpipe->redirectors)
    {
        while (xpipe->redirectors[*i])
        {
            free(xpipe->redirectors[*i]);
            xpipe->redirectors[*i] = NULL;  // Prevent double free
            (*i)++;
        }
        free(xpipe->redirectors);
        xpipe->redirectors = NULL;
    }
    *i = 0;
    if (xpipe->args)
    {
        while (xpipe->args[*i])
        {
            free(xpipe->args[*i]);
            xpipe->args[*i] = NULL;
            (*i)++;
        }
        free(xpipe->args);
        xpipe->args = NULL;
    }
}

/*
 * clean_lst_helper2 - Frees other string fields in the t_exec_pipe node.
 */
static void clean_lst_helper2(t_exec_pipe *xpipe)
{
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
}

/*
 * clean_lst - Recursively frees a linked list of t_exec_pipe nodes.
 *
 * This function calls the two helper functions to free allocated arrays and strings,
 * recurses on the next pointer, and then frees the current node.
 */
void clean_lst(t_exec_pipe *xpipe)
{
    int i;

    if (!xpipe)
        return;
    clean_lst_helper(xpipe, &i);
    clean_lst_helper2(xpipe);
    if (xpipe->next)
    {
        clean_lst(xpipe->next);
        xpipe->next = NULL;
    }
    free(xpipe);
}


void cleanup_helper(t_str *stru)
{
    if (stru->tree)
    {
        free_tree(stru->tree);
        stru->tree = NULL;
    }
    if (stru->tokens)
    {
        free_tokens(stru->tokens);
        stru->tokens = NULL;
    }
}

void cleanup(t_str *stru)
{
    if (getpid() != stru->parent_pid)
        return;  // Only parent should run cleanup
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
    cleanup_helper(stru);
}
