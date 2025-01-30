/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:25:33 by aortmann          #+#    #+#             */
/*   Updated: 2024/01/07 18:05:24 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	num[11];
	int		mod;
	int		i;

	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
		write(fd, "-", 1);
	i = 0;
	while (n != 0)
	{
		mod = n % 10;
		n /= 10;
		if (mod < 0)
			mod *= -1;
		num[i] = mod + 48;
		i++;
	}
	i--;
	while (i >= 0)
	{
		write(fd, &num[i], 1);
		i--;
	}
}
