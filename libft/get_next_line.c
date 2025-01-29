/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:21:57 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/08/22 13:01:09 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readfile(int fd, char *str, char *buffer)
{
	char	*tmp;
	int		bufferread;

	bufferread = 1;
	while (bufferread > 0)
	{
		bufferread = read(fd, buffer, BUFFER_SIZE);
		if (bufferread == -1)
		{
			free(str);
			return (NULL);
		}
		if (bufferread == 0)
			break ;
		buffer[bufferread] = '\0';
		if (str == NULL)
			str = ft_strdup("");
		tmp = str;
		str = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (str);
}

char	*ft_freeline(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0' || str[1] == '\0')
		return (NULL);
	line = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (*line == 0)
	{
		free(line);
		line = NULL;
	}
	str[i + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buffer;
	static char		*str;	

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
	{
		free(str);
		free(buffer);
		str = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = ft_readfile(fd, str, buffer);
	free(buffer);
	buffer = NULL;
	if (line == NULL)
		return (NULL);
	str = ft_freeline(line);
	return (line);
}

/* FT_READFILE EXPLANATION
This Function is designed to read content from a file descriptor (fd)
and return it as a string.
1. It uses a loop to repeatedly read from the file descriptor into a buffer
2. For each read operation:
#24 it checks if there was an error (bufferread == -1).
#26 If so, it free the existing string and returns NULL.
#29 If it reaches the end of the file (bufferread == 0),
#30 it breaks the loop.
3. After each successful read:
#31 It null-terminates the buffer, because other functions expect
the input to be null-terminated.
#32 if the string is empty, it initializes ft_strdup with an empty string.
this ensures that str always points to a valid memory location
containing a properly formated C string (even if empty)
#35 it joins the existing string with the newly read buffer content
#36 it frees the old string to prevent memory leaks.
4. The loop continues until:
#38 we search in the buffer if we read a \n or not
#38 if yes, we can break out of the loop
#38 if not, we go in the loop once again to read more from the file. 
5. Finally it returns the complete string that was read from the file.
*/

/* FT_FREELINE EXPLANATION
This Function is designed to handle a string (a line read from a file)
and prepare it for the next read operation.
1. It finds the position of the first newline character (\n) in the string.
and stores its index in i.
2. If there's no newline or if the string is very short (1 Character or less),
it returns NULL.
3. If a newline is found, it creates a substring from str
starting just after the first newline character,
and extending to the end of the string.
The starting index for the substring will be i + 1 position right after the \n
and the length of the substring will be the length fron str - i,
because we already calculated the number of character including newline.
4. If this new string is empty, it frees the memory and set the pointer to NULL
5. It then truncates the original string at the newline character,
effectively keeping only the current line,
i + 1 is the position immediately after the newline.
by placing a null terminator atr i + 1, we effectively end the string.
It keeps the current line (including the \n) and discards everything after it.
6. Finally it returns the substring that contains the content after  the \n.
*/

/* GET_NEXT_LINE EXPLANATION
This Function reads the next line from a file descriptor (fd)
and returns the extracted line.
We set a static char variable called *str. By making it static,
its value is preserved between mutliple calls to get_next_line.
This allows the function to remember where it left of in the file between reads
1. Buffer Allocation:
It allocates memory for a buffer to read data from the file.
The buffer size is defined by BUFFER_SIZE + 1 for the null-terminator.
If the buffer allocation fails, it returns NULL.
2. Error Checking:
it checks for invalid conditions.
If BUFFER_SIZE is less than or equal to 0, 
a 0 or a negative doesn't make sense for reading.
or if the fd is invalid, in UNIX-like systems valid fd are non-negative ints
or if a read test fails, 
it checks if the fd is readable without actually reading any data,
it attempts to read 0 bytes from the fd.
if any of these occur it frees any previously allocated memory
for 'str' and 'buffer' and returns NULL.
3. Reading File: 
It calls the 'ft_readfile' function to read data from the file (fd)
into the buffer and store it in the static string.
After reading, it frees the buffer as its no longer needed.
4. Line Extraction:
If line returns NULL, indicating an error or end of file,
it returns NULL. Otherwise, it calls 'ft_freeline' to extract the next line
from line and update str to hold any remaining data.
Finally it returns the extracted line.
*/