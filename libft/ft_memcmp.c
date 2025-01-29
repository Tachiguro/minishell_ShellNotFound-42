/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:44 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/21 10:58:31 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_memcmp(const void *str1, const void *str2, size_t len)
{
	unsigned int	i;
	const char		*a = str1;
	const char		*b = str2;

	i = 0;
	while (i < len)
	{
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	const char s1[20] = "Hello there!";
// 	const char s2[20] = "How are you?";
// 	char ret;

// 	ret = ft_memcmp(s1, s2, 20);

// 	if (ret < 0)
// 		printf("str1 '%s' is less than str2 '%s'\n", s1, s2);
// 	else if (ret > 0)
// 		printf("str1 '%s' is bigger than str2 '%s'\n", s1, s2);
// 	else
// 		printf("both strings are equal!\n");
// 	return (0);
// }

// FUNCTION EXPLANATION
// the function is used to compare two memory blocks (array of bytes)
// and return an integer value
// indicating their relationship it takes 3 arguments
// 'str1' and 'str2'
// these are pointers to the memory blocks that need to be compared
// 'len' this is the number of bytes to be compared from each memory block
// #22: the function declares an unsigned integer variable 'i'
// #18-19: and two constant character pointers 'a' and 'b'
// #18-19: which are initialized with 'str1' and 'str2' respectively.
// #22: the 'i' variable is initialized to 0.
// #23: the function enters a loop that continues until 'i' is less than len
// #25: inside the loop, the function compares the bytes at the 'i'th position
// #25: of the two memory blocks (a[i] and b[i])
// #26: if the bytes are not equal, the function returns the difference
// #26: between the two bytes, after casting them to unsigned characters.
// #26: this difference will be a non-zero value
// #26: indicating that the memory blocks are not equal. 