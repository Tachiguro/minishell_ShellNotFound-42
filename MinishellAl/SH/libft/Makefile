NAME	=	libft.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM = rm -rf
SRCS	=	ft_lstsize.c ft_strncmp.c ft_putnbr_fd.c ft_strjoin.c ft_memcmp.c ft_strdup.c \
			ft_lstsize.c ft_strncmp.c ft_putnbr_fd.c ft_strjoin.c ft_memcmp.c ft_strdup.c \
			ft_lstnew.c ft_atoi.c ft_print_int.c ft_arraydup.c ft_bzero.c ft_isprint.c \
			ft_putstr_fd.c ft_strtrim.c ft_striteri.c ft_lstadd_front.c ft_memset.c ft_xappend.c \
			ft_toupper.c ft_strcmp.c ft_isalpha.c ft_isalnum.c ft_memchr.c ft_print_uint.c \
			ft_tolower.c ft_strrchr.c ft_calloc.c ft_print_char.c ft_split.c ft_strchr.c \
			ft_lstiter.c ft_isdigit.c ft_memmove.c ft_strmapi.c ft_numlen.c ft_memcpy.c \
			ft_lstdelone.c ft_strlen.c ft_isascii.c ft_itoa.c ft_lstlast.c ft_strlcpy.c \
			ft_print_str.c ft_print_hex.c ft_putendl_fd.c ft_substr.c ft_strlcat.c ft_strnstr.c \
			ft_printf.c ft_lstmap.c ft_putchar_fd.c ft_lstadd_back.c ft_print_ptr.c ft_lstclear.c \
			ft_strcpy.c ft_arradd.c ft_strcat.c




OBJ_DIR = obj
OBJS =			$(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: %.c libft.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re fclean clean
