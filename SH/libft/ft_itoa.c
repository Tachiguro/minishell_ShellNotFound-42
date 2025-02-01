/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:28:39 by jherzog           #+#    #+#             */
/*   Updated: 2023/11/14 16:21:33 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlength(long n)
{
	int	counter;

	counter = 0;
	if (n < 0)
	{
		n *= -1;
		counter++;
	}
	while (n > 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

static char	*itostr(long n, int l, char *number)
{
	int	i;

	i = 0;
	number[l] = '\0';
	if (n < 0)
	{
		number[0] = '-';
		n *= -1;
		i = 1;
	}
	while (--l >= i)
	{
		if (n > 9)
		{
			number[l] = (n % 10) + '0';
			n = n / 10;
		}
		else
			number[l] = n + '0';
	}
	return (number);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		len;

	if (n == 0 || n == -0)
		return (ft_strdup("0"));
	len = nbrlength(n);
	number = (char *)malloc ((len + 1) * sizeof(char));
	if (!number)
		return (NULL);
	return (itostr(n, len, number));
}
