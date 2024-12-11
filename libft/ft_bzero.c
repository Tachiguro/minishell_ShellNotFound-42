/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:11 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 09:38:38 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (len)
	{
		*ptr = 0;
		ptr++;
		len--;
	}
}

// int main(void)
// {
// 	char str[5] = "Hello";

// 	printf("Before bzero: %s\n", str);
// 	ft_bzero(str, 5);
// 	int i = 0;
// 	while (i < 5)
// 	{
// 		printf("%d ", str[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);
// }

// FUNCTION EXPLANATION
// #16: the function takes two arguments.
// #16: a void pointer (void *s) 
// #16: to the memory area to be filled with zeroes.
// #16: size_t (len) the numbers of bytes to be zeroed.
// #18: a unsigned char pointer (*ptr) is created.
// #18: and assigned the value of (s) 
// #18: after type casting it to (char *)
// #21-26: the function enters a loop
// #21-26: that continues until (len) becomes zero
// #23: the value at the memory location pointed to by (ptr)
// #23: is set to zero (*ptr = 0).
// #24: the pointer (ptr) is incremented
// #24: to point to the next memory location (ptr++)
// #25: the value of (len)is decremented (len--)