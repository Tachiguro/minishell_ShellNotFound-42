/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:40 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 09:57:13 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static unsigned int	ft_int_length(int nb)
{
	unsigned int	len;

	len = 0;
	if (nb == 0)
		return (1);
	else if (nb < 0)
		len++;
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	unsigned int	len;
	char			*str;

	len = ft_int_length(n);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		nb = (unsigned int)-n;
	}
	else
		nb = (unsigned int)n;
	if (n == 0)
		str[0] = '0';
	while (nb)
	{
		len--;
		str[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (str);
}

// int main(void)
// {
// 	int	numbers[] = {42, -2147483648, 2147483647, 0};
// 	int count = sizeof(numbers) / sizeof(numbers[0]);
// 	int i = 0;

// 	while (i < count)
// 	{
// 		char *result = ft_itoa(numbers[i]);
// 		if (result)
// 		{
// 			printf("Integer: %d\n", numbers[i]);
// 			printf("String : %s\n\n", result);
// 			free(result);
// 		}
// 		else
// 		{
// 			printf("Memory allocation failed for %d\n\n", numbers[i]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// ft_int_len EXPLANATION
// the function takes an integer 'nb' as input
// #18-20: it initializes an unsigned int variable len to 0
// #18-20: which will store the length of the string representation of nb.
// #21-22: it checks if nb is equal to 0 if so it returns 1,
// #21-22: because the string representation of 0 has one character.
// #23: if nb is negative, it increments len by 1 to account for the '-' sign.
// #25: it enters a while loop that continues as long as nb is not 0.
// #27: inside the loop, it increments len by 1.
// #28: it updates nb by dividing it by 10 (integer division)
// #28: to remove the last digit.
// #30: after the loop, it returns the final value of len,
// #30: which represents the length of the string representation of nb.

// ft_itoa EXPLANATION
// the function takes an integer 'n' as input
// it initializes 3 variables:
// #35: 'nb' to store the absolute value of 'n'
// #36: 'len' to store the length of the string representation of 'n'
// #37: 'str' to store the dynamically allocated string.
// #39: it calls 'ft_int_length' to calculate the length
// #39: of the string representation of 'n' and stores it in 'len'
// #40: it dynamically allocates memory for the string using malloc,
// #40: allocating 'len + 1' bytes (to include the null terminator).
// #41: if memory allocation fails, it returns NULL.
// #43: it sets the last character of the string to the null terminator '\0'.
// #44: it checks if n is negative:
// #46: if so it sets the first character of the string to '-',
// #47: and assigns the absolute value of 'n' to 'nb'.
// #50: if not, it assigns 'n' directly to 'nb'.
// #51: if 'n' is 0,
// #52: it sets the first character of the string to 0.
// #53: it enters a while loop that continues as long as nb is not 0.
// #55: inside the loop it decrements len by -1 to correctly populate
// #55: the string representation of the integer
// #55: from the least significant digit to the most significant sigit.
// #56: it calculates the last digit of nb using nb % 10
// #56: and adds 48 to convert it to the corresponding ASCII character.
// #57: it updates nb by dividing it by 10 (integer division)
// #57: to remove the last digit.
// #59: after the loop, it returns the dynamically allocated string str.

// MAIN EXPLANATION
// #64: the main function initializes an array of integers called numbers
// #65: it calculates the number of elements in the numbers array 
// #65: using sizeof and stores it in the variable count.
// #66: it inititalizes an integer variable i to 0,
// #66: which will be used as an index for the numbers array
// #68: it enters a while loop that continues as long as i is less than count.
// #70: inside the loop it calls 'ft_itoa(numbers[i])'
// #70: to convert the current integer in the numbers array to a string
// #70: and stores the result in the result variable.
// #71: it checks if result is not NULL
// #73: if so it prints the current integer using printf with the format %d.
// #74: it prints the string represantation of the integer using printf
// #74: with the format %s.
// #75: it frees the dynamically allocated memory using free(result).
// #79: if result is NULL it prints an error message
// #79: indicating that memory allocation failed for the current integer.
// #81: it increments i by 1 to move to the next integer
// #81: in the numbers array.
// #83: finally it returns 0 to indicate succesful execution.