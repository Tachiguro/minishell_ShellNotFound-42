#ifndef SH_H
# define SH_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

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

t_tree	*parse_tokens(t_token **head);
void	print_tree(t_tree *root, int indent);
void	free_tree(t_tree *root);

// buildins
void	ft_exit(char *line);

// utils
void	print_tokens(t_token *head);
void	free_tokens(t_token *head);

#endif
