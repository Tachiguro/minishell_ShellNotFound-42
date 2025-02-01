/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:50:47 by jherzog           #+#    #+#             */
/*   Updated: 2025/01/29 14:42:24 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_exit(char *line)
{
	free(line);
	clear_history();
	exit(0);
}

// void	ft_echo(char *text)
// //TODO: -n inplement
// {
// 	ft_printf("%s", text);
// }
