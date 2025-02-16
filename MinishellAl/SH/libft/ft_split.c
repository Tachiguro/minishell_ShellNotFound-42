/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherzog <jherzog@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:29:20 by jherzog           #+#    #+#             */
/*   Updated: 2023/12/07 13:33:25 by jherzog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_substrs(const char *s, char c)
{
	size_t	i;
	size_t	cnt_substrs;

	i = 0;
	cnt_substrs = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			cnt_substrs++;
		}
	}
	return (cnt_substrs);
}

static char	*create_substr(const char *s, char c, size_t *pos)
{
	size_t	i;
	char	*substr;

	while (s[*pos] == c)
		(*pos)++;
	i = *pos;
	while (s[i] != c && s[i] != '\0')
		i++;
	substr = ft_substr(s, *pos, i - *pos);
	if (!substr)
		return (NULL);
	*pos = i;
	return (substr);
}

static void	free_arr(char **arr, int index)
{
	while (0 <= --index)
	{
		free(arr[index]);
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	cnt_substrs;
	size_t	pos;
	char	**strs_array;

	if (!s)
		return (0);
	i = 0;
	pos = 0;
	cnt_substrs = count_substrs(s, c);
	strs_array = malloc((cnt_substrs + 1) * sizeof(char *));
	if (!strs_array)
		return (0);
	while (i < cnt_substrs)
	{
		strs_array[i] = create_substr(s, c, &pos);
		if (!strs_array[i])
		{
			free_arr(strs_array, i);
			return (0);
		}
		i++;
	}
	strs_array[i] = NULL;
	return (strs_array);
}
