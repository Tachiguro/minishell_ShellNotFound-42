/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:46 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 10:06:21 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// int main(void)
// {
// 	char str[] = "123456781234567";
// 	char dest[20];

// 	printf("original string: %s\n", str);
// 	ft_memcpy(dest, str, 16);
// 	dest[16] = '\0';
// 	printf("ft_memcpy string: %s\n", dest);
// 	return (0);
// }

// FUNCTION EXPLANATION
// #15: the function takes 3 arguments.
// #15: dest (void *dest) the destination where data will be copied to
// #15: src (const void *src) the source from where data will be copied
// #15: len (size_t len) the number of bytes to copy.
// #17: this is a temporary pointer that points to the destination memory block
// #22: it is cast to an unsigned char to allow byte by byte manipulation.
// #18: this is a temporary pointer, that points to the source memory block,
// #23: it is also cast into an unsigned char for byte by byte manipulation.
// #19: this is a counter variable used in the loop,
// #19: to iterate through the bytes being copied.
// #22: this checks if both 'dest' and 'src' are NULL,
// #23: if they are, the function returns NULL because theres nothing to copy.
// MEMORY COPY LOOP
// #27: while the index is lower than the length of the string,
// #29-30: it copies 'len' bytes from 'src' to 'dest' one byte at a time.
// #32 the function returns the destination pointer.