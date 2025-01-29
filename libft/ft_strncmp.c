/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:15 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 10:36:46 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	unsigned int	i;

	i = 0;
	if (len == 0)
		return (0);
	while (i < len && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == len)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

// int main(void)
// {
// 	const char s1[20] = "Hello there!";
// 	const char s2[20] = "Hello there!";
// 	int ret;

// 	ret = ft_strncmp(s1, s2, 20);

// 	if (ret < 0)
// 		printf("str1 '%s' is less than str2 '%s'\n", s1, s2);
// 	else if (ret > 0)
// 		printf("str1 '%s' is bigger than str2 '%s'\n", s1, s2);
// 	else
// 		printf("both strings are equal!\n");
// 	return (0);
// }

// FUNCTION EXPLANATION
// the function essentially compares the characters of the two strings
// one by one, up to the specified length (len)
// or until a null character or a different character is encountered
// #16: the function is used to compare two strings up to a max length
// #16: it returns an interger value indicating the relationship between
// #16: the two strings.
// #20: the function initializes an unsigned int i variable (i = 0)
// #21: if len is 0 (len == 0) the function returns 0 immediately
// #21: indicating that the strings are equal.
// #23: the function enters a loop that continues
// #23: as long as i is less than len (i < len) and both str1 and str2
// #23: are non-null characters (\0)
// #23: and the characters at those positions are equal
// #24: inside the loop the value of i is incremented by 1 (i++)
// #25: if the loop terminates because i has reached len
// #25: it means that the first len characters of both strings are equal
// #26: so the function returns 0 indicating that both strings are equal
// #27: if the loop terminates because a null character
// #27: or a different character is encountered in one of the strings
// #27: the function returns the difference between
// #27: the unsigned char values of the characters at position i in str1
// #27: and str2, this difference represents the lexiographical
// #27: relationship between the two strings.