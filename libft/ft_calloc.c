/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:14 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 09:40:12 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	int		*a;

	if (count == 0 || size == 0)
		return (malloc(0));
	i = count * size;
	a = malloc(i);
	if (a == NULL)
		return (NULL);
	ft_bzero(a, i);
	return (a);
}

// int main(void)
// {
// 	unsigned int cnt;
// 	unsigned int sz;
// 	int			*arr;

// 	cnt = 5;
// 	sz = sizeof(int);
// 	arr = (int *)ft_calloc(cnt, sz);

// 	if (arr == NULL)
// 	{
// 		printf("Memory allocation failed!\n");
// 		return (1);
// 	}
// 	printf("Allocated array: %d %d %d %d %d\n", 
// 			arr[0], arr[1], arr[2], arr[3], arr[4]);
// 	free(arr);
// 	return (0);
// }

// FUNCTION EXPLANATION
// the function is used to dynamically allocate memory
// for an array of elements and initialze them to zero.
// #17: the function takes two arguments:
// #17: count (size_t count) the number of elements to be allocated.
// #17: size (size_t size) the size of each element in bytes.
// #19: we create an size_t variable to store the later result.
// #20: we create an int pointer that stores the returned pointer,
// #20: to the allocated memory.
// #22: it first checks if either 'count' or 'size' is zero.
// #23: if so it returns the result of calling malloc(0),
// #23: this ensures that a valid pointer is returned, even if the size is zero
// #24: we then allocate the calculated size of i and assign it to a
// #26: if allocation fails it returns 'NULL'
// #28: it calls the ft_bzero function,
// #28: to initialize all the allocated memory to zero.
// #29: it then returns the pointer 'a'
// #29: to the allocated and initialized memory.

// MAIN EXPLANATION
// it declares 3 variables:
// #36: an unsigned int cnt (count).
// #37: an unsigned int sz (size).
// #38: and an int *arr (pointer to the allocated memory)
// #40: it assigns values to 'cnt' (5).
// #41: and sz the size of an int in bytes, obtained by sizeof(int).
// #42: it calls the ft_calloc function with cnt and sz as arguments
// #42: and assigns the returned pointer to 'arr'.
// #44: it checks if the memory allocation was successful (arr != NULL)
// #46: if not, it prints an error message and returns 1 (indicating failure)
// #49: if the allocation is successful,
// #49: it prints the contents of the allocated array which are all zeros
// #51: it frees the allocated memory using the 'free' function.
// #52: finally it returns 0 (indicating success).