/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:20 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 11:01:46 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strtrim(const char *str1, const char *set)
{
	const char	*start;
	const char	*end;
	char		*result;
	size_t		len;

	if (str1 == NULL || set == NULL)
		return (NULL);
	start = str1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = str1 + ft_strlen(str1) - 1;
	while (end >= start && ft_strchr(set, *end))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, start, len);
	result[len] = '\0';
	return (result);
}

// int main(void)
// {
// 	const char	*src;
// 	char		*trim;
// 	char		*cut;

// 	src = "ebebebebBeep Boopebebebeb";
// 	trim = "be";
// 	cut = ft_strtrim(src, trim);
// 	printf("Original string: %s\n", src);
// 	printf("Trimmed string: %s\n", cut);
// 	return (0);
// 	free (cut);
// }

// FUNCTION EXPLANATION
// this function trims (removes) specified characters from the beginning
// and end of a string.
// It takes 2 const char pointers as input:
// str1 (the string to trim)
// set (the set of characters to trim)
// it returns a char pointer to the newly trimmed string.
// it also relies on 3 helper functions:
// ft_strchr: searches for a character in a string.
// ft_strlen: calculates the length of a string.
// ft_memcpy: copies memory from one location to another.
// #18-21: we declare 4 variables:
// #18: *start, this pointer is used to find the first character in str1,
// #18: that is not in the 'set'.
// #18: it starts at the beginning of str1 and moves forward,
// #18: until it finds a character not in 'set'.
// #19: *end, this pointer is used to find the last character in str1,
// #19: that is not in the 'set'.
// #19: it starts at the end of str1 and moves backwards,
// #19: until it finds a character not in 'set'.
// #20: *result this is the pointer to the newly allocated memory,
// #20: where the trimmed string will be stored.
// #20: it it the variable that will be returned by the function.
// #21: this variable stores the length of the trimmed string.
// #21: it is calculated as 'end - start + 1'.
// #23: it first checks if either str1 or set is NULL, if so it returns NULL
// #26: it uses the pointer 'start' to find the first character in str1,
// #26: that is not in the set.
// #27: it does this by moving 'start' forward,
// #27: while the current character is foun in 'set'.
// #28: it sets 'end' to point to the last character of str1
// #29: it then moves 'end' backwards,
// #29: while the current character is found in 'set'.
// #31: the new length is calculated as 'end - start + 1'.
// #32: it allocates memory for the new string using 'malloc'.
// #32: the size allocated is 'len + 1' to account for the null terminator.
// #33-34: if allocation fails, it returns NULL.
// #35: it uses 'ft_memcpy' to copy the trimmed portion of the string,
// #35-36: to the new memory, it then adds a null terminator at the end.
// #37: finally it returns the pointer to the new trimmed string.