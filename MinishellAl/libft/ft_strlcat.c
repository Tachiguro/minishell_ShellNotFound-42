/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:28:00 by aortmann          #+#    #+#             */
/*   Updated: 2024/01/09 10:28:20 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	dstsize;
	unsigned int	srcsize;

	dstsize = ft_strlen(dst);
	srcsize = ft_strlen(src);
	if (size == 0 || size < dstsize)
		return (srcsize + size);
	i = 0;
	while (src[i] != '\0' && dstsize + i < size - 1)
	{
		dst[dstsize + i] = src[i];
		i++;
	}
	dst[dstsize + i] = '\0';
	return (dstsize + srcsize);
}
