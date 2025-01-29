/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:42 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 10:02:02 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	*ft_memchr(const void *str, int c, size_t len)
{
	unsigned char	*s;
	unsigned char	ch;

	s = (unsigned char *)str;
	ch = (unsigned char)c;
	while (len > 0)
	{
		if (*s == ch)
			return (s);
		s++;
		len--;
	}
	return (NULL);
}

// int main(void)
// {
// 	const char str1[] = "Hello there";
// 	const char ch = ' ';
// 	char *ret;

// 	ret = ft_memchr(str1, ch, ft_strlen(str1));
// 	if(ret == NULL)
// 		printf("Character '%c' not found!\n", ch);
// 	else
// 		printf("Character '%c' found at position: %ld.\n", ch, ret - str1);
// 	return (0);
// }

// FUNCTION EXPLANATION
// the function is used to search for the first occurence
// of a specific character 'c' within a given memory block 'str'
// of a specified length 'len' it returns a pointer to the location
// of the first occurence of the character, or NULL if the char is not found
// #16: the function takes 3 arguments:
// #16: const void *str: a pointer to the memory block to be searched
// #16: int c: the character to search for, represented as an integer
// #16: size_t len: the length of the memory block to be searched
// #18-19: variable declarations:
// #18: 's': a pointer to the memory block cast to an unsigned char pointer
// #18: for easier character manipulation
// #19: 'ch': the character to search for, cast to an unsigned char value.
// #21-22: initialization:
// #21: the 'str' pointer is cast to an unsigned char pointer
// #21: and assigned to 's'
// #22: the character 'c' is cast to an unsigned char value
// #22: and assigned to 'ch'
// #23-28: search loop:
// #23: the loop iterates over the memory block
// #23: until the end is reached 'len' becomes 0
// #25: in each iteration it checks if the current character
// #25: pointed to by 's' is equal to the character 'ch'
// #26: if a match is found, it returns a pointer
// #26: to the location of the character 's'
// #27: if no match is found, it moves to the next character
// #27: by incrementing 's' and decrementing 'len'
// #30: if the loop completes without finding the character
// #30: it returns NULL, indicating that the character was not found