CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = sh
TEST_NAME = tests/run_tests

LIBFT = libft/libft.a
LIBFT_DIR = libft

OBJDIR = obj
TEST_OBJDIR = tests/obj

LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

SRC =	error_handling.c	\
		syntax.c			\
		buildins.c			\
		tokenization.c		\
		utils.c				\
		parser.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

MAIN_SRC = sh.c
MAIN_OBJ = $(MAIN_SRC:%.c=$(OBJDIR)/%.o)

TEST_SRC =	syntax_tests.c			\
			tokenization_tests.c	\
			tests.c
TEST_OBJ = $(addprefix $(TEST_OBJDIR)/, $(TEST_SRC:.c=.o))

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MAIN_OBJ) $(LDFLAGS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

test: $(TEST_OBJDIR) $(TEST_OBJ) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(OBJ) $(LDFLAGS) -o $(TEST_NAME)
	./$(TEST_NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJDIR)/%.o: tests/%.c | $(TEST_OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR) $(TEST_OBJDIR):
	mkdir -p $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(MAIN_OBJ)
	rm -rf $(OBJDIR) $(TEST_OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(TEST_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test
