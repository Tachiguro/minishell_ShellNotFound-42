/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 23:38:48 by jherzog           #+#    #+#             */
/*   Updated: 2025/01/22 22:53:27 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *str)
{
	int	counter;
	int	len;

	counter = 0;
	if (!str)
		return (write(1, "(null)", 6));
	len = ft_strlen(str);
	counter = write(1, str, len);
	if (counter == -1)
		return (-1);
	return (counter);
}
