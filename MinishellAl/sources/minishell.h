/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:10:44 by bjbogisc          #+#    #+#             */
/*   Updated: 2025/01/28 18:11:34 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h> //added
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <termios.h>
# include <signal.h>
# include <stdlib.h> //added
# include <sys/types.h> //added
# include <sys/wait.h> //added
# include <dirent.h> //added
# include <termcap.h> //added
# include <errno.h>
# include <stdbool.h>

# define BUF 100 //buffer für input

//struct für variablen
typedef struct s_environ
{
	char	**env;

}	t_env;

typedef struct s_str
{
	char	**args;
	char	*flags;
}	t_vars;

typedef struct s_execution
{
	char	*candidate;
	char	*full_path;
	char	*path_env;
	char	**paths;
	char	*temp;
}	t_exec;

typedef struct s_xlist //execution list fill me in tokenization
{
	char			**redirectors;
	char			*outfile;
	char			*new_out;
	char			*infile;
	char			*new_in;
	char			**flags;
	char			**args;
	struct s_xlist	*next;
	char			*cmd;
	char			*re;
}	t_exec_pipe;

typedef struct s_structs //struct with references for all other structs
{
	t_env		*environs;
	t_exec_pipe	*xpipe;
	t_vars		*vars;
	t_exec		*exe;
}	t_str;

//linked list

char	*get_env_value(const char *key, char **envp);
char	*find_executable_path(char *cmd, t_str *str);
void	ft_fprintf(int stream, char *str);
void	ft_echo(char *str, char *flag);
bool	check_redirect(t_str *stru);
void	exec_pipeline(t_str *stru);
int		contains_slash(char *cmd);
void	ft_cd(const char *path);
int		is_built_in(char *cmd);
void	init_env(t_env *envi);
void	ft_unset(char *name);
int		ft_exit(char **args);
int		ft_pwd(void);
void	ft_env(void);
#endif