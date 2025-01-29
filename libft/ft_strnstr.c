/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:29:41 by jherzog           #+#    #+#             */
/*   Updated: 2023/07/13 18:30:03 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (counter < len && haystack[counter] != '\0')
	{
		i = 0;
		while ((haystack[counter + i] == needle[i]) && ((counter + i) < len))
		{
			if (haystack[counter + i] == needle[i] && needle[i + 1] == '\0')
				return ((char *)haystack + counter);
			i++;
		}
		counter++;
	}
	return (NULL);
}
