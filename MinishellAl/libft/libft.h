/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:25:33 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/26 21:17:03 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>

#define LLONG_MIN_MANUAL (-9223372036854775807LL - 1)

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char			*ft_xappend(char *str1, char *str2, bool space, int clean);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				ft_memcmp(const void *s1, const void *s2, unsigned int n);
unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);
unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			*ft_memcpy(void *dest, const void *src, unsigned int n);
char			*ft_strnstr(const char *haystack, const char *needle,
					unsigned int len);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_calloc(unsigned int nmemb, unsigned int size);
void			*ft_memchr(const void *s, int c, unsigned int n);
int				ft_strcmp(const char *str1, const char *str2);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_strjoin(const char *s1, const char *s2);
void			*ft_memset(void *s, int c, unsigned int n);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
char			*ft_strrchr(const char *s, int c);
char			**ft_split(const char *s, char c);
char			*ft_strchr(const char *s, int c);
void			*ft_bzero(void *str, size_t n);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
char			*ft_strdup(const char *src);
void			ft_putnbr_fd(int n, int fd);
int				ft_atoi(const char *nptr);
char			*ft_itoa(long long int n);
t_list			*ft_lstnew(void *content);
int				ft_strlen(const char *s);
t_list			*ft_lstlast(t_list *lst);
int				ft_lstsize(t_list *lst);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

#endif