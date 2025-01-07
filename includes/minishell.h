/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:10:44 by bjbogisc          #+#    #+#             */
/*   Updated: 2025/01/06 17:25:30 by aortmann         ###   ########.fr       */
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





char		*promt(void);
void		ft_pwd(void);

#endif