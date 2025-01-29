/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:58:46 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/24 09:36:25 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strrchr(const char *str, int c)
{
	int		i;

	i = ft_strlen(str);
	if (str[i] == (char)c)
		return ((char *)str + i);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}

// int main(void)
// {
// 	const char str[] = "Hello there";
//     char *ret;

//     ret = ft_strrchr(str, '\0');
//     if (ret != NULL)
//         printf("last occurence of '%c' in '%s' was at position %ld.\n", 
// 				*ret, str, ret - str);
//     else
//         printf("character not found in '%s'\n", str);
//     return (0);
// }

// FUNCTION EXPLANATION
// This function finds the last occurence of a character in a string
// it returns a pointer to the last occurence of c (int c) in str (str)
// or NULL (\0) if c is not found
// #16: the function takes two parameters:
// #16: (const char *str) this is the input string in which we are searching
// #16: for the character.
// #16: (int c) this is the character we are looking for,
// #16: passed as an integer.
// #18: this declares an interger variable 'i'
// #19: this sets 'i' to the length of the string.
// CHECK THE LAST CHARACTER
// #20: this checks if the character at the end of the string,
// #20: which is the null terminator is equal to 'c'
// #21: if it is, the function returns a pointer to this position in the string
// LOOP TO FIND THE LAST OCCURENCE
// #22: this loop runs from the end if the string to the beginning.
// #24: inside the loop it checks if the current character str[i] is equal to c
// #25: if it finds the character, it returns a pointer to this position
// #26: decrements 'i' to move to the previous character in the next iteration
// #28: if the loop completes without finding the character,
// #28: the function returns NUL indicating that the character was not found.