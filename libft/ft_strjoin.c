/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:03 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/20 14:05:08 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strjoin(const char *str1, const char *str2)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*slen;
	char			*start;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	slen = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (slen == NULL)
		return (NULL);
	start = slen;
	while (*str1)
		*slen++ = *str1++;
	while (*str2)
		*slen++ = *str2++;
	*slen = '\0';
	return (start);
}

// int main(void)
// {
// 	const char	*src1;
// 	const char	*src2;
// 	char		*join;
// 	src1 = "Beep";
// 	src2 = " Boop";
// 	join = ft_strjoin(src1, src2);
// 	printf("String 1: %s\n", src1);
// 	printf("String 2: %s\n", src2);
// 	printf("Combined string: %s\n", join);
// 	free(join);
// 	return (0);
// }