/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:07 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 10:20:46 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (src[count])
		count++;
	if (size < 1)
		return (count);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (count);
}

// int	main(void)
// {
// 	char str[] = "Hello there!";
// 	char dest[20];

// 	printf("original string: %s\n", str);
// 	ft_strlcpy(dest, str, 13);
// 	printf("ft_strlcpy string: %s\n", dest);
// 	return (0);
// }

// FUNCTION EXPLANATION
// #16: the function takes 3 arguments.
// #16: dest (char *dest) a pointer to the destination buffer 
// #16: where the string will be copied
// #16: src (const char *src) a pointer to the source that will be copied.
// #16: size (size_t size) the maximum number of bytes
// #16: that can be copied to the destination buffer
// #16: including the null terminator (\0)
// #18-19: the function initialized 2 unsigned integer variables.
// #18: i variable is used as an index counter
// #18: to keep track of the number of characters
// #18: being copied from the source string (src).
// #19: count variable is used to store the length of the source string
// #21-24: by iterating over the characters
// #21: until the null terminator (\0) is encountered
// #25-26: if the size (size_t size) argument is less than 1
// #25-26: the function returns the length of the source string (count)
// #25-26: without copying anything to the destination buffer.
// #27: if size (size_t size) is greater than or equal to 1,
// #27: the function enters a loop
// #27: that copies characters from the source string 
// #27: to the destination buffer.
// #27: the size - 1 condition ensures that there is always space left
// #27: in the destination buffer for the null terminator (\0)
// #29-30: the loop continues until either the null terminator (\0)
// #29-30: of the source string is reached (src[i])
// #29-30: or the maximum number of characters (size - 1) has been copied.
// #32: after the loop the function explicitly adds a null terminator (\0)
// #32: to the destination buffer (dest[i]).
// #33: the function returns the length of the source string (count),
// #33: regardless of wether the entire string was copied or not.