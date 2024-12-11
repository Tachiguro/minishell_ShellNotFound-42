NAME							= minishell

# Compiler and Cflags
CC								= cc
CFLAGS							= -Wall -Wextra -Werror -g
LDFLAGS							= -lreadline
RM								= rm -f
RMDIR							= rm -rf

# Directories
SRC_DIR							= sources/
OBJ_DIR							= objects/
INCLS							= -I ./includes/
LIBFT_DIR						= ./libft

# Sources
SRC								= $(SRC_DIR)prompt.c $(SRC_DIR)pwd.c $(SRC_DIR)read_input_test.c\



# Object Files
OBJ								= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT							= $(LIBFT_DIR)/libft.a
LIBINCL							= -L $(LIBFT_DIR) -lft

# Dependencies
DEPS							= $(OBJ:%.o=%.d)

# Object Directory Rule
$(OBJ_DIR)/%.o:					$(SRC_DIR)%.c | $(OBJ_DIR)
								$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(SRC_DIR) -c $< -o $@ $(INCLS)

# All Rule
all:							$(NAME)
								@echo "\033[4;36m[Program is ready]\033[0m"

# Name Rule
$(NAME):						$(LIBFT) $(OBJ)
								$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LIBINCL) $(LDFLAGS)
								@echo "\033[4;36m[minishell created]\033[0m"

# Libft Rule
$(LIBFT):
								@$(MAKE) -C $(LIBFT_DIR) all
								@echo "\033[4;36m[Libft created]\033[0m"

# Object Directory Creation
$(OBJ_DIR):
								@mkdir -p $(OBJ_DIR)

-include $(DEPS)

# Clean Rule
clean:
								@$(MAKE) -C $(LIBFT_DIR) clean
								$(RMDIR) $(OBJ_DIR)
								@echo "\033[4;36m[Cleaned up]\033[0m"

# Fully Clean Rule
fclean:							clean
								@$(MAKE) -C $(LIBFT_DIR) fclean
								$(RM) $(NAME)
								@echo "\033[4;36m[Fully Cleaned up]\033[0m"

# Rebuild Rule
re:								fclean
								$(MAKE) all -s

# Phony Targets
.PHONY:							all clean fclean re
