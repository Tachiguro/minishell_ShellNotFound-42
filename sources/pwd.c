/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:21:04 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/12/10 12:14:58 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the current working directory
static int	ft_pwd(void)
{
	char	*cwd;
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (NULL);
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}