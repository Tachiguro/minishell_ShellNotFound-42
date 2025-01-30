/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:30:33 by aortmann          #+#    #+#             */
/*   Updated: 2024/01/19 10:47:32 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, unsigned int len)
{
	unsigned int	needle_len;
	size_t			i;
	size_t			j;

	i = 0;
	needle_len = ft_strlen(needle) - 1;
	if (needle_len + 1 == 0)
		return ((char *) haystack);
	if (len == 0)
		return (0);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while ((haystack[i + j] == needle[j] && needle[j] != '\0'
				&& (i + j) < len))
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
