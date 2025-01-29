/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:59:55 by jherzog           #+#    #+#             */
/*   Updated: 2025/01/22 22:47:29 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle_p( va_list args)
{
	int	counter;
	int	second_counter;

	counter = ft_print_str("0x");
	if (counter == -1)
		return (-1);
	second_counter = ft_print_ptr(va_arg(args, unsigned long));
	if (second_counter == -1)
		return (-1);
	return (counter + second_counter);
}

static int	ft_check_format(const char *f, int i, va_list args)
{
	if (f[i] == '%')
		return (ft_print_char('%'));
	else if (f[i] == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (f[i] == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (f[i] == 'd' || f[i] == 'i')
		return (ft_print_int(va_arg(args, int)));
	else if (f[i] == 'u')
		return (ft_print_uint(va_arg(args, unsigned int)));
	else if (f[i] == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 'a'));
	else if (f[i] == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 'A'));
	else if (f[i] == 'p')
		return (ft_handle_p(args));
	return (-1);
}

int	ft_printf(const char *f, ...)
{
	va_list	args;
	int		i;
	int		counter;
	int		tempc;

	i = 0;
	counter = 0;
	tempc = 0;
	if (!f)
		return (0);
	va_start(args, f);
	while (f[i])
	{
		if (f[i] == '%')
			tempc = ft_check_format(f, ++i, args);
		else
			tempc = ft_print_char(f[i]);
		if (tempc == -1)
			return (-1);
		counter += tempc;
		i++;
	}
	va_end(args);
	return (counter);
}
