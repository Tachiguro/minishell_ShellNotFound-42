# **************************************************************************** #
#                                   MINISHELL                                  #
# **************************************************************************** #

NAME            = minishell
CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
LIBFT_PATH      = ../libft
LIBFT           = $(LIBFT_PATH)/libft.a

# ------------------------------------------------------------------------------
# Sources / Objects
# ------------------------------------------------------------------------------
# Example: adjust to list **all** your Minishell .c files
SRCS			= built_in_commands.c built_in_commands2.c exec_test.c exec_utils.c execute.c redirect.c \
				enivronmental.c exec_pipeline.c

OBJS            = $(SRCS:.c=.o)

# ------------------------------------------------------------------------------
# Rules
# ------------------------------------------------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	# 1) Build libft (it creates libft.a in ../libft)
	make -C $(LIBFT_PATH)
	# 2) Link minishell with libft
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft -o $(NAME)

%.o: %.c
	# Compile each .c into .o, 
	# and include the path to libft.h if needed:
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

clean:
	# Remove minishell .o files
	rm -f $(OBJS)
	# Also call clean on libft
	make -C $(LIBFT_PATH) clean

fclean: clean
	# Remove minishell executable
	rm -f $(NAME)
	# Also remove libft.a
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
