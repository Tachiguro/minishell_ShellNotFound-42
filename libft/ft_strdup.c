/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:00 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/21 10:57:39 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	i = 0;
	if (new == NULL)
		return (NULL);
	while (*src)
	{
		new[i] = *src++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

// int main(void)
// {
// 	char	*src;
// 	char	*s1;

// 	src = "Beep Boop";
// 	s1 = ft_strdup(src);
// 	printf("|%s|\n", s1);
// 	free(s1);
// 	return (0);
// }

// FUNCTION EXPLANATION
// the function creates a new string that is a duplicate
// of the string pointed to bt 'src'.
// #16: the function takes a const char * pointer called 'src'
// #16: as an argument.
// #18-19: inside the function we declare 2 variables:
// #18: char *new, 'new' will hold the address
// #18: of the dynamically allocated memory for the duplicated string.
// #19: int i, 'i' will be used as a loop counter.
// #21: Here we use 'malloc' to allocate memory for the duplicated string.
// #21: the size of the memory block is calculated by multiplying
// #21: the size of a chat by the length of the source string (ft_strlen(src))
// #21: plus an additional byte for the null terminator ('+1')
// #21: the result is cast to 'char *' and assigned to new.
// #22: we initialize i to 0.
// #23: we check if 'malloc' was successful by comparing new to 'NULL'
// #23: it means the memory allocation failed, so we return NULL.
// #25: this is the main loop,
// #27: new[i] assigns the character pointed to by 'src' to the 'i'-th position
// #27: 'src++' increments the 'src' pointer to point to the next character
// #27: in the source string.
// #28: 'i++' increments the loop counter 'i' to move to the next character
// #28: in the 'new' string
// #30: after the loop we add the null terminator
// #30: to the end of the 'new' string.
// #31: finally we return the 'new' string
// #31: which now contains a duplicate of the source string.