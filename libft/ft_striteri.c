/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:02 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/24 14:47:08 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_striteri(char *str, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str == NULL || f == NULL)
		{
			break ;
		}
		f(i, str + i);
		i++;
	}
}

// void	uppercase(unsigned int i, char *c)
// {
// 	(void)i;
// 	*c = ft_toupper(*c);
// }

// int	main(void)
// {
// 	char	str[] = "aaaa";

// 	ft_striteri(str, uppercase);
// 	printf("%s\n", str);
// 	return (0);
// }

// FUNCTION EXPLANATION
// The function is used to apply the function 'f' to each character,
// of the string 'str' passing the index of the current character as the first,
// argument to 'f' and a pointer to the current character as the second argumen
// the function takes 2 arguments:
// char *str: a pointer to a string
// void (*f)(unsigned int, char*): a pointer to a function,
// that takes 2 arguments: an unsigned int and a pointer to a char.
// #18: it initializes an unsigned int variable 'i' to 0.
// #21: it enters a lopp that continues as long as the character at index 'i'
// #21: in 'str' is not the null terminator '\0'.
// #23: inside the loop it checks if either 'str' or 'f' is NULL,
// #25: if either is NULL it breaks out of the loop.
// #27: it calls the function 'f' with the current index 'i'
// #27: and a pointer to the current character in 'str' as arguments
// #28: it increments 'i' to move to the next character in 'str'
// UPPERCASE EXPLANATION
// this purpose of uppercase is to convert the character pointed to by 'c'
// to uppercase using the ft_toupper function.
// it takes 2 arguments:
// unsigned int i: an unsigned int that is not used in this function (void)
// char *c: a pointer to a char