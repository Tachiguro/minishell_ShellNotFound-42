/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:05:58 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/10/10 11:32:03 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_type(const char *format, va_list ap)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += print_char(va_arg(ap, int));
	else if (*format == 's')
		count += print_string(va_arg(ap, char *));
	else if (*format == 'p')
		count += print_pointer(va_arg(ap, void *));
	else if (*format == 'd' || *format == 'i')
		count += print_int(va_arg(ap, int));
	else if (*format == 'u')
		count += print_unsigned(va_arg(ap, unsigned int));
	else if (*format == 'x')
		count += print_hex(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (*format == 'X')
		count += print_hex(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (*format == '%')
		count += print_percent();
	return (count);
}

int	ft_printf(const char *input, ...)
{
	int		i;
	int		j;
	va_list	ap;

	i = 0;
	j = 0;
	va_start(ap, input);
	while (input[i])
	{
		if (input[i] == '%')
		{
			i++;
			j += check_type(&input[i], ap);
		}
		else
		{
			j++;
			write(2, &input[i], 1);
		}
		i++;
	}
	va_end(ap);
	return (j);
}

// VARIADIC FUNCTIONS EXPLANATION
// Variadic functions are functions which take a variable number of arguments
// the functions are declared with an ellipsis (...) in the parameter list,
// indicating that they can take any number of additional arguments,
// beyond the specified fixed parameters.
// example: 'int printf(const char *format, ...);'
// Variadic function Macros/Type
// ----------va_list-----------
// This is a type that represents a list of variable arguments.
// it is used to store and manage the variable arguments
// passed to a variadic function.
// ----------va_start----------
// This macro initializes the 'va_list'
// by setting it to the first variable argument.
// It requires the last fixed parameter (the one before the ellipsis)
// as an argument.
// it takes two arguments as parameters:
// ap: this is a 'va_list' type variable
// parmN: this is the last fixed parameter in the function
// ----------va_arg------------
// This macro retrieves the next argument from the 'va_list'
// and returns its value. It increments the 'va_list'
// to point to the next argument.
// it takes two arguments as parameters:
// ap: this is a 'va_list" type variable
// that points to the current position in the argument list
// type: this is the type of the argument to be retrieved.
// ----------va_copy-----------
// This macro creates a copy of a 'va_list'.
// It is used to duplicate a 'va_list' so that it can be reused or passed
// to another function without affecting the original list.
// That can be used independently of the original list.
// this is necessary because 'va_list' is not a simple pointer
// and cannot be copied using a simple assignment.
// ----------va_end-----------
// This macro cleans up the 'va_list' after it has been used.

// CHECK TYPE EXPLANATION
// this function is used to print different types of data
// based on a format string.
// it initializes a variable 'count' to 0.
// This variable will keep track of the number of characters printed.
// it checks the first character of the format string '*format'.
// based on this character, it decides what type of data to print.
// if the format character is 'c', it prints a single character.
// if the format character is 's', it prints a string.
// if the format character is 'p', it prints a pointer.
// if the format character is 'd' or 'i', it prints a signed integer.
// if the format character is 'u', it prints an unsigned integer.
// if the format character is 'x', it prints an unsigned integer
// in hexadecimal format (lowercase).
// if the format character is 'X', it prints an unsigned integer
// in hexadecimal format (uppercase).
// if the format character is '%', it prints a percent sign.
// Finally, it returns the total count of characters printed.