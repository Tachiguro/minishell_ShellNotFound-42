/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:51:20 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/12/11 13:00:34 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*promt(void)
{
	char	*input;

	input = readline("TachiguroShell :> ");
	if (input && *input)
		add_history(input);
	if (!input)
	{
		printf("Until next time!");
		rl_clear_history();
		exit (0);
	}
	return (input);
}
