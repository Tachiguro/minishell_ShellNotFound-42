/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:16:24 by aortmann          #+#    #+#             */
/*   Updated: 2024/01/20 00:35:20 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.*/

#include "libft.h"

int	ft_nbrlen(long long int i)
{
	int	j;

	j = 0;
	while (i != 0)
	{
		j++;
		i /= 10;
	}
	return (j);
}

int	ft_is_negative(long long int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*allocate_mem(int slen)
{
	char	*ret;

	ret = (char *)malloc((slen + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret[slen] = '\0';
	return (ret);
}

char	*ft_check_flag(int flag, long long int n, int slen, char *ret)
{
	long long int	min_manual;

	min_manual = LLONG_MIN_MANUAL;
	if (flag && n == min_manual)
	{
		ret[0] = '-';
		n = -(n + 1);
	}
	else if (flag)
	{
		ret[0] = '-';
		n = -n;
	}
	while (n != 0 && slen > 0)
	{
		ret[flag + slen - 1] = n % 10 + '0';
		n /= 10;
		slen--;
	}
	return (ret);
}

char	*ft_itoa(long long int n)
{
	int		flag;
	int		slen;
	char	*ret;
	char	*result;

	slen = ft_nbrlen(n);
	flag = ft_is_negative(n);
	if (n == 0)
	{
		ret = allocate_mem(1);
		if (ret == NULL)
			return (NULL);
		ret[0] = '0';
		return (ret);
	}
	ret = allocate_mem(slen + flag);
	if (ret == NULL)
	{
		return (NULL);
	}
	result = ft_check_flag(flag, n, slen, ret);
	return (result);
}
