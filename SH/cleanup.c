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
void clean_exec(t_exec *exe)
{
    int i;

    i = 0;
    if (exe->candidate)
        free(exe->candidate);
    if (exe->full_path)
        free(exe->full_path);
    if (exe->path_env)
        free(exe->path_env);
    if (exe->candidate)
        free(exe->candidate);
    if (exe->candidate)
        free(exe->candidate);
    if (exe->paths)
    {
        while (exe->paths[i])
        {
            free(exe->paths[i]);
            i++;
        }
        free(exe->paths);
    }
    if (exe->temp)
        free(exe->temp);
    
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
            xpipe->redirectors[i] = NULL;
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
    if (xpipe->outfile)
    {
        free(xpipe->outfile);
        xpipe->outfile = NULL;
    }

    if (xpipe->new_out)
    {
        free(xpipe->new_out);
        xpipe->new_out = NULL;
    }
    if (xpipe->infile)
    {
        free(xpipe->infile);
        xpipe->infile = NULL;
    }
    if (xpipe->new_in)
    {
        free(xpipe->new_in);
        xpipe->new_in = NULL;
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
    if (xpipe->next)
    {
        clean_lst(xpipe->next);
        xpipe->next = NULL;
    }
    free(xpipe);
    xpipe = NULL;
}



void cleanup(t_str *stru)
{
    clean_lst(stru->xpipe);
    clean_exec(stru->exe);
}