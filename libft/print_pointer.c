/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:06:41 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/08/15 11:44:04 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_pointer(void *ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return (print_string("(nil)"));
	i += print_string("0x");
	i += print_hex((size_t)ptr, "0123456789abcdef");
	return (i);
}
// %p - print a pointer address in hexadecimal