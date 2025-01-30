/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:13:52 by aortmann          #+#    #+#             */
/*   Updated: 2024/01/19 10:48:19 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_num(char c, int num)
{
	num *= 10;
	num += c - 48;
	return (num);
}

static int	ignore_space(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] != '\0' || (nptr[i] >= 48 && nptr[i] <= 57))
	{
		if (nptr[i] != ' ' && nptr[i] != '\t' && nptr[i] != '\v'
			&& nptr[i] != '\n' && nptr[i] != '\r' && nptr[i] != '\f')
			break ;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	isneg;

	num = 0;
	i = ignore_space(nptr);
	isneg = 0;
	if ((nptr[i] == '-' || nptr[i] == '+')
		&& (nptr[i + 1] >= 48 && nptr[i + 1] <= 57))
	{
		if (nptr[i] == '-')
			isneg = 1;
		i++;
	}
	while (nptr[i] != '\0')
	{
		if (nptr[i] >= 48 && nptr[i] <= 57)
			num = convert_num(nptr[i], num);
		else
			break ;
		i++;
	}
	if (isneg == 1)
		num *= -1;
	return (num);
}
