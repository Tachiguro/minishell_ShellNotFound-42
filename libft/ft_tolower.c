/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:57:26 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/13 10:53:02 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c = c + 32;
		return (c);
	}
	else
		return (c);
}

// int main(void)
// {
// 	char ch;

// 	ch = 'A';
// 	printf("Before the conversion: %c\n", ch);
// 	ft_tolower(ch);
// 	printf("After the conversion: %c\n", ft_tolower(ch));
// 	return (0);
// }