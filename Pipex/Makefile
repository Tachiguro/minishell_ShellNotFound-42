#$(NAME)

# Program Name
NAME = pipex

# Source files (only .c files)
SRC = pipex.c

# Compiler options
OPTIONS = -Wall -Wextra -Werror

# Object files (corresponding to .c files)
OBJ = $(SRC:.c=.o)

# Default target to build the program
all: $(NAME)

# Create the executable by linking object files
$(NAME): $(OBJ)
	cc $(OPTIONS) -o $(NAME) $(OBJ)

# Compile .c files into .o files
%.o: %.c
	cc $(OPTIONS) -c $< -o $@

# Clean object files
clean:
	/bin/rm -f $(OBJ)

# Rebuild everything (clean + build)
re: clean all