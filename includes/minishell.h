/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:10:44 by bjbogisc          #+#    #+#             */
/*   Updated: 2025/01/29 16:52:31 by aortmann         ###   ########.fr       */
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
# include "parser.h"
# include <stdlib.h> //added
# include <sys/types.h> //added
# include <sys/wait.h> //added
# include <dirent.h> //added
# include <termcap.h> //added

# define BUF 100 //buffer für input

//struct für variablen
typedef struct s_variables
{

}	t_vars;

//linked list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;


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


char		*promt(void);
void		ft_pwd(void);

#endif