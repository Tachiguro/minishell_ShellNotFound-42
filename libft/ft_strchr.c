/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:18 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/21 13:40:36 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

// int main(void)
// {
// 	const char str[] = "Hello there";
//     char *ret;

//     ret = ft_strchr(str, 'e');
// 	// ret = ft_strchr(str + 1, ' ');
//     if (ret != NULL)
//         printf("first occurence of '%c' in '%s' was at position %ld.\n", 
// 				*ret, str, ret - str);
//     else
//         printf("character not found in '%s'\n", str);
// 	// while (ret != NULL)
// 	// {
// 	// 	printf("Space found at position %ld.\n", ret - str);
// 	// 	ret = ft_strchr(ret + 1, ' ');
// 	// }
//     return (0);
// }

// FUNCTION EXPLANATION
// This function finds the first occurence of a character in a string
// it returns a pointer to the first occurence of c (int c) in str (str)
// or NULL (\0) if c is not found
// #16: the function takes two parameters:
// #16: str (const char *str) a string to search in
// #16: c (int c) the character to search for
// #18: the function iterates through the string (str) using a while loop
// #18: until it reaches the end of the string i.e. until *str is equal to \0
// #20: inside the loop it checks if the current character (*str) is equal to c
// #20: if yes, the function returns a pointer to current position in the string
// #24: if c is not found and is not equal to \0 the function returns NULL
// MAIN:
// #31: this line declares a character array
// #31: the 'const' keyword means that the contents of the array
// #31: cannot be modified after initialization.
// #32: this line declares a pointer to a character named ret
// #32: the pointer ret is used to store the result of the ft_strchr function
// #34: this line calls ft_strchr with two arguments
// #34: 'str' the string to search in.
// #34: 't' the character to search for.
// #36: the condition ret != '\0' checks 
// #36: if the pointer ret returned by ft_strchr
// #36: is not equal to the null terminator (\0)
// #36: this means it checks if the character 't' was found in the string.
// #36: if the condition is true i.e. 't' was found
// #37: the first printf statement is executed.
// #37: %c format specifier is used to print the character pointed by ret (*ret)
// #37: %ld format specifier is used to print the position
// #37: of the found in the string.
// #37: the expression 'ret - str' calculates the difference between pointer ret
// #37: and the base adress of the string (str) this difference represents
// #37: the position of the character 't' in the string.
// #38: if the condition is false i.e. 't' was not found
// #38: the sexcond printf staement is executed.
// #39: the message 'not found' is printed
// #39: to indicate that the character was not found