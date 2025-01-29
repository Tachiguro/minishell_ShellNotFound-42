/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:56 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/06/27 10:26:09 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

// Function to count the number of words in the string
static int	word_count(const char *str, char c)
{
	unsigned int	cnt;
	unsigned int	j;

	cnt = 0;
	j = 0;
	while (*str != '\0')
	{
		if (*str != c && j == 0)
		{
			j = 1;
			cnt++;
		}
		else if (*str == c)
			j = 0;
		str++;
	}
	return (cnt);
}

// Function to calculate the length of a word
static size_t	word_len(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0' && str[len] != c)
		len++;
	return (len);
}

// Function to free the allocated memory for the result array
static void	free_array(char **result)
{
	int	i;

	i = 0;
	if (result == NULL)
		return ;
	while (result[i] != NULL)
	{
		free (result[i]);
		i++;
	}
	free (result);
}

// Function to fill the allocated memory for the result array
static char	**fill_array(char **res, const char *str, char c, size_t word_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < word_count)
	{
		while (str[j] && str[j] == c)
			j++;
		res[i] = ft_substr(str, j, word_len(&str[j], c));
		if (res[i] == NULL)
		{
			free_array(res);
			return (NULL);
		}
		while (str[j] && str[j] != c)
			j++;
		i++;
	}
	res[i] = (NULL);
	return (res);
}

// Main ft_split function
char	**ft_split(const char *str, char c)
{
	size_t	cnt;
	char	**res;

	cnt = word_count(str, c);
	res = malloc(sizeof(char *) * (cnt + 1));
	if (res == NULL)
		return (NULL);
	if (fill_array(res, str, c, cnt) == NULL)
	{
		free_array(res);
		return (NULL);
	}
	return (res);
}

//Main function to test ft_split
// int main(void)
// {
// 	char 	str[] = "Hello! im a Robot, Beep Boop!";
// 	char 	delim = ' ';
// 	char 	**res;
// 	int		i = 0;

// 	res = ft_split(str, delim);
// 	if (res == NULL)
// 	{
// 		printf("Memory allocation failed!\n");
// 		return (1);
// 	}
// 	while (res[i] != NULL)
// 	{
// 		printf("result[%d]: %s\n", i, res[i]);
// 		i++;
// 	}
// 	free_array (res);
// 	return (0);
// }

// WORD_COUNT EXPLANATION
// this function takes 2 arguments:
// const char *str: a pointer to a null terminates string.
// char c: a character for the delimiter.
// the purpose is to count the number of words in the input string 'str',
// where a word is defined as a sequence of characters that are not equal
// to the character 'c'
// #19-20: the function inititalizes 2 variables and both are initialized to 0
// #19: unsigned int cnt: the word count.
// #20: unsigned int j: a flag to track wether the current character is part
// #20: of a word or not.
// #24: the function enters a while loop that continues as long as the current,
// #24: character pointed to by 'str' is not the null terminator
// #26: inside the loop the function checks the current character:
// #26: if the current character is not equal to 'c' and 'j' is 0,
// #26: meaning the current character is the start of a new word.
// #29: the function increments 'cnt' (the word count)
// #28: and sets j to 1 indicating that the current character is part of a word
// #31: if the current character is equal to 'c' the function sets 'j' to 0,
// #31: to indicate that the current character is not part of a word.
// #33: after the check the function moves the pointer 'str'
// #33: to the next character in the string.
// #35: once the loop has finished i.e. the end of the string has been reached
// #35: the function returns the final value of 'cnt'.

// WORD_LEN EXPLANATION
// the function returns the length of the word in the string
// up to the first occurrence of the specified character 'c' or '\0'
// whichever comes first.
// #41: the function initializes size_t len to 0.
// #44: it enters a loop that continues as long as the character at index 'len'
// #44: in the string is not the null terminator and not the specified char 'c'
// #45: inside the loop the function increments 'len' by 1
// #45: to move to the next character in the string.
// #46: once the loop terminates either because the '\0'
// #46: or the specified character 'c' was encountered,
// #46: the function returns the final value of 'len' which 
// #46: represents the length of the word up to that point.

// FREE_ARRAY EXPLANATION
// the function takes a single argument, char **result, which is a pointer
// to the first element of the 2D array.
// #52: it initializes a variable 'i' to 0, which will be used as an index,
// #52: to iterate through the array.
// #55: it checks if the 'result' pointer is NULL,
// #55: if it is, the function simply returns without doing anything
// #57: if 'result' is not NULL the function enters a loop that continues,
// #57: as long as the current element pointed to by 'result[i] is not NULL
// #57: this means it will loop until it reaches the end of the array.
// #59: inside the loop for each non-NULL element of the array,
// #59: the function calls 'free(result[i])'
// #59: this frees the memory allocated for the array itself,
// #59: the array of pointers to strings.

// FILL_ARRAY EXPLANATION
// the function takes four parameters:
// char **res: a double pointer that will hold the resulting array of substring
// const char *str: that represents the input string to be split.
// char c: that represents the character used to separate the substring.
// size_t word_count: that represents the expected number of substrings,
// in the resulting array.
// #68-69: two variables 'i' and 'j' are used as loop counters
// #68: 'i' keeps track of the current index in the 'res' array.
// #69: 'j' keeps track of the current position in the 'str' string.
// #73: the function enters a loop that runs 'word_count' times
// #75: it skips over any leading occurence of the separator character 'c'
// #76: in the string by incrementing 'j' until,
// #76: a non-separator character is found.
// #77: it then calls the ft_substr function to create a new substring,
// #77: starting from the current position 'j' in 'str',
// #77; the length of the substring is determined by calling the 'world_len'
// #77: with'&str[j]' as the argument and 'c' as the separator character.
// #77: the resulting substring is stored in the 'res' array at the current 'i'
// #78: if the 'ft_substr' function faills to allocate memory for the substring
// #80: the function calls 'free_array' to free any previously allocated
// #80: substring in the 'res' array and returns NULL to indicate an error
// #83: after storing the substring in 'res[i]',
// #83: the function skips over the non-separator in 'str' by incrementing 'j'
// #83: until it reaches the next occurence of the separator character 'c'
// #83: or the end of the string.
// #85: finally it increments 'i' to move to the next index in the 'res' array
// #87: after the loop completes the funtion sets the last elemt of the 'res'
// #87: array at index 'i' to NULL to mark the end of the array
// #88: finally the function returns the 'res' array
// #88: which now contains the split substrings.

// FT_SPLIT EXPLANATION
// the function takes a string 'str' and a character 'c' as input
// and splitts the string into an array of substrings
// based on the specified character 'c'
// #97: the 'word_count' is called to count the number of words (substrings)
// #97: in the input string 'str' based on the delimiter character 'c',
// #97: this count is stored in the variable 'cnt'
// #98: memory is allocated for the result array 'res' using malloc,
// #98: the size of the array is cnt + 1 becuase the last element
// #99: of the array is set to NULL to indicate the end of the array
// #101: if the memory allocation is successful,
// #101: the 'fill_array' is called
// #101: to populate the 'res' array with substrings
// #101: the 'fill_array' function iterates over the input string 'str'
// #101: and performs the following steps for each word:
// #101: it skips over any leading delimiter character 'c'.
// #101: it calcutlates the length of the current word,
// #101: using the 'word_len' function.
// #101: it allocates memory for the current word using 'ft_substr'
// #101: and stores it in the 'res' array.
// #103: if the allocation fails, it frees the allocates memory for 'res' array
// #103: and returns NULL.
// #103: it skips over the current word until it reaches the next delimiter 'c'
// #103: after the 'fill_array' function populates the 'res' array,
// #103: with all the substrings, it sets the last element of the array to NULL
// #103: to indicate the end of the array
// #106: finally the 'ft_split' funtion returns the 'res' array
// #106 containing the split substrings. 