/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:07:02 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/08/15 11:44:11 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_unsigned(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr / 10 > 0)
		i += print_unsigned(nbr / 10);
	i += print_char((nbr % 10) + '0');
	return (i);
}
// %u - print an unsigned number
