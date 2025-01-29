/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:08:17 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/08/15 11:44:07 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_string(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		return (print_string("(null)"));
	}
	while (str[i])
	{
		print_char(str[i]);
		i++;
	}
	return (i);
}
// %s - print a string
