/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:29:07 by jherzog           #+#    #+#             */
/*   Updated: 2023/07/13 18:30:03 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*temp_dst;
	const char	*temp_src;
	int			i;

	temp_dst = (char *)dst;
	temp_src = (const char *)src;
	i = -1;
	if (temp_dst == temp_src || n == 0)
		return (dst);
	if (temp_dst > temp_src && temp_dst - temp_src < (int)n)
	{
		while (n-- > 0)
			temp_dst[n] = temp_src[n];
		return (dst);
	}
	if (temp_dst < temp_src && temp_src - temp_dst < (int)n)
	{
		while (++i < (int)n)
			temp_dst[i] = temp_src[i];
		return (dst);
	}
	ft_memcpy(dst, src, n);
	return (dst);
}
