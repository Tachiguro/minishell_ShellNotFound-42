# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 10:57:29 by bjbogisc          #+#    #+#              #
#    Updated: 2024/08/26 12:37:11 by bjbogisc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

SRC = ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_strlen.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_strlcpy.c\
	ft_strlcat.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strncmp.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_atoi.c\
	ft_strnstr.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_split.c\
	ft_printf.c\
	print_char.c\
	print_hex.c\
	print_int.c\
	print_percent.c\
	print_pointer.c\
	print_string.c\
	print_unsigned.c\
	get_next_line.c\
	ft_lstget.c\
	
	 
OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re