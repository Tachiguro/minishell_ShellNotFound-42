#ifndef SH_H
# define SH_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

//# include "../libft/libft.h"
# include <unistd.h> //added
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
// Grammar tests
bool	is_correct_syntax(const char *l);

// Error handling
void	print_error(const char *text);

// Tokenization
typedef enum	e_type
{
	T_WORD,		// char, string ...
	T_PIPE,		// |
	T_IN,		// <
	T_OUT,		// >
	T_APPEND	// >>
}				t_type;



typedef struct s_environ
{
	char	**env;

}	t_env;

typedef struct	s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}				t_token;

t_token	*create_tokens(char *line);

// Parsing
typedef struct s_tree
{
	t_type			type;
	int				file_type;
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

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

t_tree	*parse_tokens(t_token **head);
void	print_tree(t_tree *root, int indent);
void	free_tree(t_tree *root);

// utils
void	print_tokens(t_token *head);
void	free_tokens(t_token *head);
/////////////
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
int		ft_exit(char **args, t_str *str);
int		ft_pwd(void);
void	ft_env(void);
void 	cleanup(t_str *stru);
int exe(t_tree *tree, bool ex);

#endif
