/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:28 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/13 10:53:23 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = c -32;
		return (c);
	}
	else
		return (c);
}

// int main(void)
// {
// 	char ch;

// 	ch = '1';
// 	printf("Before conversion: %c\n", ch);
// 	ft_toupper(ch);
// 	printf("After conversion: %c\n", ft_toupper(ch));
// 	return (0);
// }