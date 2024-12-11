/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:08 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/25 09:38:04 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str > 47 && *str < 58)
	{
		res = res * 10 + *str - 48;
		str++;
	}
	return (res * sign);
}

// int main(void)
// {
// 	char *str;

// 	str = " -1234ab567";
// 	printf("%d\n", ft_atoi(str));
// 	return (0);
// }

// FUNCTION EXPLANATION
// the function takes a string (const char *str) as input
// and converts it to an integer value
// the function handles leading whitespace characters
// optional sign characters (+ or -)
// and converts the subsequent digits to their corresponding int value
// #18-19: variable declaration:
// #18: 'res' is initialized to 0 which will store the converted int value
// #19: 'sign' is initialized to 1 representing a positive number by default
// #23: leading whitespace handling:
// #23: the function skips over any leading whitespace characters
// #23: (space, tab, newline etc.) by incrementing the 'str' pointer
// #24: until a non-whitespace character is encountered
// #25: sign handling:
// #25: if the next character is a minus sign ('-')
// #25: the 'sign' variable is multiplied by -1
// #25: effectively making the result negative.
// #27: if the next character is a plus sign ('+')
// #27: or a minus sign ('-') the 'str' pointer is incremented
// #27: to move past the sign character.
// #29: digit conversion:
// #29: the function enters a loop that iterates
// #29: over the remaining characters in the string
// #29: for each digit character (0 to 9) the value is extracted
// #31: by substracting the ASCII value of '0' from the character (*str - '0')
// #31: the extracted value is added to the res variable
// #31: after multiplying res by 10 to shift its digit to the left
// #32: the str pointer is incremented to move to the next character
// #34: result calculation:
// #34: after the loop finishes, the function returns the final res value
// #34: multiplied by the sign value, which accounts for the sign of the number