/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 23:48:52 by jherzog           #+#    #+#             */
/*   Updated: 2025/01/22 22:53:35 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_uint(unsigned int n)
{
	int	counter;
	int	temp;

	counter = 0;
	temp = 0;
	if (n > 9)
	{
		counter = ft_print_uint(n / 10);
		if (counter == -1)
			return (-1);
		n %= 10;
	}
	temp = ft_print_char('0' + n);
	if (temp == -1)
		return (-1);
	return (counter += temp);
}
