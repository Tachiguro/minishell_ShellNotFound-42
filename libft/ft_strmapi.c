/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:14 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/24 12:07:35 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*res;

	i = 0;
	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	while (str[i])
	{
		res[i] = (*f)(i, str[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

// char	charfunc(unsigned int i, char c)
// {
// 	c += i;
// 	return (c);
// }

// int main(void)
// {
// 	char	str[] = "aaaaaaaa";

// 	printf("%s\n", ft_strmapi(str, charfunc));
// 	return (0);
// }

// FUNCTION EXPLANATION
// the function takes a string 'str' and a funtion '*f' as arguments.
// const char *str: the input string to be transformed
// char (*f)(unsigned int, char): a pointer to a function,
// that takes an unsigned integer (index) and a character and returns a char.
// it applies the function to each character of the string,
// passing the characters index and the character itself to 'f'.
// the result is a new string,
// where each character has been transformed by the function 'f'.
// VARIABLE DECLARATION
// #18: size_t i: a loop counter.
// #19: size_t len: length of the input string.
// #20: char *res: pointer to the resulting new string.
// INITIAL CHECKS/MEMORY ALLOCATION
// #22: initialize 'i' to 0.
// #23: check if 'str' is NULL, if it is return NULL.
// #25: get the length of the input string using ft_strlen.
// #26: allocate memory for the new string 'res',
// #26: which is 'len + 1' to account for the null terminator.
// #28: if memory allocation fails it returns NULL.
// TRANSFORM CHARACTERS
// #29: loop through each character of the input string.
// #31: apply the function 'f' to each character and its index,
// #31: and store the result in 'res'.
// #32: increment the loop counter 'i'.
// #34: after the loop add a null terminator to the end of the string.
// #35: finally we return the result 'res'.
// CHARFUNC EXPLANATION
// this function is used with ft_strmapi, it would shift each character,
// in the string by its index. So the first character (index 0) wouldnt change.
// The second character would shift by 1, the third by 2 and so on.
// this function takes two arguments:
// unsigned int i: for the index of the current character.
// char c: a character from the original string.
// #40: it adds the value of 'i' to the ASCII value of 'c'.
// #41: it returns this new character.