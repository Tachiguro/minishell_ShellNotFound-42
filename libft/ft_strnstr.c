/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:17 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/21 10:56:36 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (str2[0] == '\0')
		return ((char *)str1);
	i = 0;
	while (str1[i] && i < len)
	{
		j = 0;
		while (str1[i + j] == str2[j] && (i + j) < len)
		{
			if (str2[j + 1] == '\0')
				return ((char *)&str1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	const char *lstr = "Beep Boop Bap";
// 	const char *sstr = "Boop";
// 	char *res = ft_strnstr(lstr, sstr, ft_strlen(lstr));
// 	if (res)
// 		printf("Substring found: %s\n", res);
// 	else
// 		printf("Substring not found.\n");
// 	return (0);
// }

// FUNCTION EXPLANATION
// the function is used to find the first occurence
// of the string (str2) in the string (str1)
// within the first (len) characters of str1.
// it returns a pointer to the beginning of the located substring
// or NULL if the substring is not found
// #18-19: the function initializes 2 variables
// #18-19: 'i' and 'j' to keep track of the positions
// #18-19: in 'str1' and 'str2' respectively.
// #21: the Base Case: if str2 is an empty string
// #21: the function returns str1
// #21: because an empty string is considered to be present
// #21: at the beginning of every string
// #24: the outer while loop iterates over the characters
// #24: of str1 until either the end of str1 is reached
// #24: or len characters have been checked.
// #27: inside the outer loop the inner while loop checks
// #27: if the characters ar position 'i' in str1
// #27: and 'j' in str2 match
// #29: if they match it continues to check the subsequent
// #29: characters until either a mismatch is found
// #29: or the end of str2 is reached.
// #29: if the end is reached (i.e. str2[j + 1] == '\0')
// #29: it means that the entire substring str2
// #29: has been found in str1
// #30: in this case the function returns a pointer
// #30: to the beginning of the located substring
// #30: in str1 (i.e. &str1[i]).
// #33: if the inner loop exits
// #33: without finding the entire substring str2
// #33: the outer loop increments 'i' to move to the next char in str1.
// #35: if the outer loop completes without finding str2 in str1
// #35: the function returns NULL to indicate that the substring was not found