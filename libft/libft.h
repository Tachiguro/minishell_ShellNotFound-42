/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:43:12 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/08/26 13:49:36 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* --- Check Functions --- */
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);

/* --- Memory Functions --- */
void	ft_bzero(void *s, size_t len);
void	*ft_memset(void *s, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *str, int c, size_t len);
int		ft_memcmp(const void *str1, const void *str2, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t len);

/* --- String Functions --- */
size_t	ft_strlen(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t len);
char	*ft_strnstr(const char *str1, const char *str2, size_t len);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strdup(const char *src);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(const char *str1, const char *str2);
char	*ft_strtrim(const char *str1, const char *set);
char	**ft_split(const char *str, char c);
char	*ft_strmapi(const char *str, char (*f)(unsigned int, char));
void	ft_striteri(char *str, void (*f)(unsigned int, char*));

/* --- Write Functions --- */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);

/* --- Printf Functions --- */
int		ft_printf(const char *input, ...);
int		print_char(int c);
int		print_hex(size_t n, char *hex);
int		print_int(long nbr);
int		print_percent(void);
int		print_pointer(void *ptr);
int		print_string(char *str);
int		print_unsigned(unsigned int nbr);

/* --- GNL Functions --- */
char	*ft_readfile(int fd, char *str, char *buffer);
char	*ft_freeline(char *str);
char	*get_next_line(int fd);

/* --- Linked Lists --- */
t_list	*ft_lstget(t_list *lst, int index);

#endif