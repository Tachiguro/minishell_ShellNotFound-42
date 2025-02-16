/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:29:05 by jherzog           #+#    #+#             */
/*   Updated: 2023/07/13 18:30:03 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*temp_src;
	char		*temp_dst;

	temp_src = (char *)src;
	temp_dst = (char *)dst;
	if (!dst && !src && n > 0)
		return (0);
	while (n--)
		*temp_dst++ = *temp_src++;
	return (dst);
}
