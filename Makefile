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

# Sources
SRC								= $(SRC_DIR)sources\



# Object Files
OBJ								= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

# Dependencies
DEPS							= $(OBJ:%.o=%.d)

# Object Directory Rule
$(OBJ_DIR)/%.o:					$(SRC_DIR)%.c | $(OBJ_DIR)
								$(CC) $(CFLAGS) -I $(SRC_DIR) -c $< -o $@ $(INCLS)

# All Rule
all:							$(NAME)
								@echo "\033[4;36m[Program is ready]\033[0m"

# Name Rule
$(NAME):						$(OBJ)
								$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LDFLAGS)
								@echo "\033[4;36m[minishell created]\033[0m"

# Object Directory Creation
$(OBJ_DIR):
								@mkdir -p $(OBJ_DIR)

-include $(DEPS)

# Clean Rule
clean:
								$(RMDIR) $(OBJ_DIR)
								@echo "\033[4;36m[Cleaned up]\033[0m"

# Fully Clean Rule
fclean:							clean
								$(RM) $(NAME)
								@echo "\033[4;36m[Fully Cleaned up]\033[0m"

# Rebuild Rule
re:								fclean
								$(MAKE) all -s

# Phony Targets
.PHONY:							all clean fclean re
