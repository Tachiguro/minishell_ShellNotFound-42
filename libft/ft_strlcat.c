/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:06 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/21 10:57:25 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	ldest;
	size_t	lsrc;
	size_t	i;

	ldest = ft_strlen(dest);
	lsrc = ft_strlen(src);
	if (size == 0)
		return (lsrc);
	if (ldest >= size)
		return (lsrc + size);
	i = 0;
	while (src[i] && ldest + i < size - 1)
	{
		dest[ldest + i] = src[i];
		i++;
	}
	dest[ldest + i] = '\0';
	return (ldest + lsrc);
}

// int main(void)
// {
// 	char dest[20] = "Hello, ";
// 	char src[] = "World!";

// 	printf("original string: %s\n", dest);
// 	ft_strlcat(dest, src, sizeof(dest));
// 	printf("final string: %s\n", dest);
// 	return (0);
// }

// FUNCTION EXPLANATION
// #16: the ft_strlcat function is a string manipulation function
// #16: that concatenates the src string to the dest string, with a size limit
// #16: dest (char *dest) the destination string
// #16: where the src (const cahr *src) string will be append.
// #16: src (const char *src) the source string that will br appended to dest
// #16: size the maximum size of the dest buffer, including the null terminator
// #22-23: the function first calculates the lengths
// #22-23  of dest and src strings using the ft_strlen function.
// #25-26: if size (size_t size) is 0 it returns the length if src (lsrc)
// #25-26: as no concatenation can be performed.
// #27: if the length of dest (ldest) is greater than or equal to size
// #27: it means that the dest buffer is already full
// #28: and the function returns the sum of size and the length of src (lsrc).
// #30-33: otherwise the function enters a loop that appends characters
// #30-33: from src to dest until either the end of src is reached
// #30-33: or the remaining spaces in dest (including \0) is exhausted
// #34: after the loop the function adds a null temrinator to dest
// #34: to ensure it remains a valid string.
// #35: finally the function returns the sum of the initial ldest and lsrc.