/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:53:41 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/26 22:14:07 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Implement stru->exes (| character). The output of each command in the stru->exeline is
// connected to the input of the nstru->exet command via a stru->exe.

bool	check_redirect(t_str *stru) //assumes that a list is inside stru structure
{
	// printf("check redirect continue need list from here on \n");
	// exit(0);
	if (!stru->xpipe->redirectors) //if redirectors array is empty return
		return (0);
	return (1);
}
