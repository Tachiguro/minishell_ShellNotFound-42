/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xappend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:56:04 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/26 21:24:41 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	populate_str1(char *str1, char *ret, bool space, int *i)
{
	while (str1[*(i)])
	{
		ret[*i] = str1[*i];
		(*i)++;
	}
	if (space)
	{
		ret[*i] = ' ';
		(*i)++;
	}
}

static void	populate_str2(char *str2, char *ret, int *j, int *i)
{
	while (str2[*j])
	{
		ret[*i] = str2[*j];
		(*i)++;
		(*j)++;
	}
	ret[*i] = '\0';
}

static void	clean_strings(char *str1, char *str2, int clean)
{
	if (clean == 1)
	{
		if (str1)
			free(str1);
	}
	else if (clean == 2)
	{
		if (str2)
			free(str2);
	}
	else
	{
		if (str1)
			free(str1);
		if (str2)
			free(str2);
	}
}

char	*ft_xappend(char *str1, char *str2, bool space, int clean)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str1) + ft_strlen(str2);
	if (space)
		ret = malloc(sizeof(char) * (len + 2));
	else
		ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	populate_str1(str1, ret, space, &i);
	populate_str2(str2, ret, &j, &i);
	if (clean)
		clean_strings(str1, str2, clean);
	return (ret);
}
