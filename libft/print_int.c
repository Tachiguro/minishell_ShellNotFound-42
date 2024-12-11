/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:27:16 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/08/15 11:43:54 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_int(long nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		i += print_char('-');
		nbr = -nbr;
	}
	if (nbr / 10)
		i += print_int(nbr / 10);
	i += print_char((nbr % 10) + '0');
	return (i);
}
// %d/%i - print a decimal (base 10 )number or an integer in base 10.
