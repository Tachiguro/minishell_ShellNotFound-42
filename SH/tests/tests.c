/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:14:24 by jherzog           #+#    #+#             */
/*   Updated: 2025/02/01 14:15:54 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include <assert.h>
#include <stdio.h>

int	main()
{
	ft_printf("Running all tests...\n");
	test_syntax();
	test_tokenization();
	ft_printf("All tests passed!\n");

	return (0);
}
