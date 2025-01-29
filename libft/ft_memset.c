/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:49 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 11:08:44 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*i;

	i = (unsigned char *) s;
	while (len > 0)
	{
		*i = c;
		i++;
		len--;
	}
	return (s);
}

// int	main(void)
// {
// 	char	str[20] = "Hello, how are you?";

// 	printf("\nBefore memset(): %s\n", str);
// 	ft_memset(str, '.',7*sizeof(char));
// 	printf("After memset(): %s\n", str);
// 	return (0);
// }

// FUNCTION EXPLANATION
// #18: this line declares a character pointer (i).
// #18: that will be used to iterate over the memory block
// #20: this line type casts the (void *) to a (char *) and assigns it to (i).
// #20: this is necessary because 
// #20: the function needs to treat the memory block as an array of bytes.
// #21-25: main loop. it iterates over the memory block.
// #21-25: and fills each bytes with the specific value (c).
// #23: the value (c) is assigned to the byte pointed to by (i).
// #24: the pointer (i) is incremented
// #24: to point to the next byte in the memory block.
// #25: the counter (n) is decremented
// #25: to keep track of the remaining bytes to be filled.
// #26: the loop continues until (n) becomes zero
// #26: which means that all bytes in the memory block have been filled.
// #27: the function returns the original pointer (s)
// #27: which now points to the filled memory block.