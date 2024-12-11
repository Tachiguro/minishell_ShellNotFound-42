/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:21:04 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/12/11 13:38:58 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the current working directory
void	ft_pwd(void) // unsicher welchen typ ich nutzen soll....
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
}
