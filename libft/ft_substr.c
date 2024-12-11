/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:24 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/24 09:37:00 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*slen;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (start > ft_strlen(str))
		len = 0;
	else if (len > (ft_strlen(str) - start))
		len = ft_strlen(str) - start;
	slen = malloc(sizeof(char) * (len + 1));
	if (slen == NULL)
		return (NULL);
	while (i < len && str[start])
	{
		slen[i] = str[start];
		i++;
		start++;
	}
	slen[i] = '\0';
	return (slen);
}

// int	main(void)
// {
// 	char	*src;
// 	char	*sub;	
// 	src = "Beep Boop Bap";
// 	sub = ft_substr(src, 5, 4);
// 	printf("Original string: %s\n", src);
// 	printf("Substring: |%s|\n", sub);
// 	return (0);
// 	free (sub);
// }

// FUNCTION EXPLANATION
// the function is designed to create a new string from a given string,
// starting at a specified position 'start' and having a spcified length 'len'
// #15: the function takes 3 arguments:
// #15: const char str: the original string,
// #15: from which the sunstring will be created.
// #15: unsigned int start: the starting index in the original string,
// #15: from where the substring will begin.
// #15: size_t len: the length of the substring to be created.
// #17: unsigned int i: a counter for the loop.
// #18: char *slen: a pointer to hold the newly created substring.
// #20: if the input string is NULL,
// #21: the function returns NULL.
// ADJUST LENGTH
// #22: if 'start' is greater than the length of 'str',
// #23: set 'len' to 0
// #23: because the starting position is beyond the end of the string.
// #24: if 'len' is greater than the remaining characters from 'start'
// #24: to the end of the string,
// #25: adjust 'len' to the number of characters from start to the end
// MEMORy ALLOCATION
// #26: allocate memory for the new substring, which is len + 1
// #26: to account for the null terminator
// #27: if allocation fails it returns NULL
// COPY CHARACTERS
// #29: this loop is responsible for copying characters
// #29: from the origianl string to the new substring
// #29: the loop continues as long as i is less than len
// #29: and if we havent reached the end of the original string.
// #31: this line copies a character from the original string 'str'
// #31: at index 'start' to the new substring 'slen' at index 'i'
// INDEX INCREMENTS
// 32: i is incremented to move to the next position in the new substring
// 33: start is incremented to move to the nex character in the original string
// #35: after copying the characters, add a null terminator
// #35: at the end of the newly created substring.
// #36: return the pointer to the newly created substring