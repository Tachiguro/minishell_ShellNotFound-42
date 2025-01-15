/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:59 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/15 18:12:19 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	ft_env(void)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		pritnf("%s\n", environ[i]);
		i++;
	}
}
