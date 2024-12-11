/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:48 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 10:09:26 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d <= s)
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	return (dest);
}

// int main(void)
// {
// 	char str1[] = "Hello";
// 	char str2[] = "World";

// 	printf("before memmove dest: %s, src: %s\n", str1, str2);
// 	ft_memmove(str1, str2, sizeof(str2));
// 	printf("after memmove dest: %s, src: %s\n", str1, str2);
// 	return (0);
// }

// FUNCTION EXPLANATION
// #16: the function takes 3 arguments.
// #16: dest (void *dest) the destination memory area.
// #16: src (const void *src) the source memory area.
// #16: len (size_t len) the number of bytes to copy.
// #18: this is a temporary pointer that points to the destination memory block
// #24: it is cast to an unsigned char to allow byte by byte manipulation.
// #19: this is a temporary pointer, that points to the source memory block,
// #25: it is also cast into an unsigned char for byte by byte manipulation.
// #20: this is a counter variable used in the loop,
// #20: to iterate through the bytes being copied.
// #22: this checks if both 'dest' and 'src' are NULL,
// #23: if they are, the function returns NULL because theres nothing to copy.
// FORWARD COPY
// #26: if the destination address is less than or equal to the source address,
// #31: the function copies the data from the start to the end,
// #31: this prevents overwriting the source data before its copied.
// BACKWARDS COPY
// #35: if the destination address is greater than the source address,
// #38: the function copies the data from the end to the start.
// #38: this ensures that the source data is no overwritten before it is copied
// #40: the function returns the original destination pointer.