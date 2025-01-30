/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:26:31 by aortmann          #+#    #+#             */
/*   Updated: 2024/01/19 07:16:13 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.*/

#include "libft.h"

static int	ft_skip_characters(const char *s, char c, int index, int flag)
{
	if (flag == 0)
	{
		while (s[index] != '\0')
		{
			if (s[index] != c)
				return (index);
			index++;
		}
		return (index);
	}
	else
	{
		while (s[index] != '\0')
		{
			if (s[index] == c)
				return (index);
			index++;
		}
		return (index);
	}
}

static char	**create_arr_strings(const char *s, char c, int i)
{
	char	**str;
	int		size;

	i = 0;
	size = 0;
	i = ft_skip_characters(s, c, i, 0);
	if (s[i] == '\0')
	{
		str = (char **)malloc(1 * sizeof(char *));
		str[0] = 0;
		return (str);
	}
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i = ft_skip_characters(s, c, i, 0);
		if (s[i] != c && s[i] != '\0')
		{
			i = ft_skip_characters(s, c, i, 1);
			size++;
		}
	}
	str = (char **)malloc((size + 1) * sizeof(char *));
	str[size] = 0;
	return (str);
}

static char	**delimeter(const char *s, char c, char **str)
{
	int	size;
	int	i;
	int	index;

	i = 0;
	size = 0;
	index = 0;
	str = create_arr_strings(s, c, i);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i = ft_skip_characters(s, c, i, 0);
		if (s[i] != c && s[i] != '\0')
		{
			size = ft_skip_characters(s, c, i, 1);
			size = size - i;
			str[index] = ft_substr(s, i, size);
			index++;
			i = i + size;
			size = 0;
		}
	}
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**temp;
	char	**ret;

	temp = (char **)malloc(sizeof(char *));
	if (temp == NULL)
	{
		return (NULL);
	}
	temp[0] = 0;
	if (s[0] == '\0')
		return (temp);
	ret = delimeter(s, c, temp);
	free(temp);
	return (ret);
}
