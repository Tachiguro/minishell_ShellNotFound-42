/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:26:55 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/08/15 11:43:50 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex(size_t n, char *hex)
{
	int	i;

	i = 0;
	if (n / 16)
		i += print_hex(n / 16, hex);
	i += print_char(hex[n % 16]);
	return (i);
}
// %x/%X - print a number in hexadecimal

// FUNCTION EXPLANATION
// the function calls itself recursively with 'n / 16' as the new argument.
// This is because the hexadecimal representation of a number
// is made up of digits, and each digit represents a value from 0 to 15.
// So the function need tio handle the most significant digit first
// then the next one and so on.
// the function uses the modulo operator '%' to get the least significant digit
// of the number 'n'. It then uses this digit as an index into the hex string,
// to get the corresponding hexadecimal character
// and calls the print_char function to print it.