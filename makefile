# Program name
NAME	= minishell

# Compiler
CC		= cc
CFLAGS  = -g -Wall -Wextra -Werror

# Libft
LIBFT_PATH	= libft_based/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC			=	-I ./includes/\
				-I ./libft_based/

# Sources  
SRC_DIR		= src/
SRC			= main.c \
			  bool.c \
			  debug.c \
			  env.c \
			  execution_protocol.c \
			  input.c \
			  redirections.c redirections_apply.c redir_heredoc.c \
			  signals.c \
			  tokenize.c t_gather_word.c t_wildcard.c t_utils.c \
			  parsing.c p_utils.c \
			  exe_pipes.c \
			  quotes.c \
			  var_utils.c \
			  ft_bin.c \
			  ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c \
# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Default target
all: $(OBJ_PATH) $(LIBFT) $(NAME)

# Rule to compile object files
$(OBJ_PATH)%.o: $(SRC_DIR)%.c
	@printf "\r\033[KCompiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Create object directory if it doesn't exist
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

# Build libft
$(LIBFT):
	@echo "Making libft..."
	@make -C $(LIBFT_PATH) --no-print-directory
	@echo "done"

# Compile the program
$(NAME): $(OBJS)
	@echo ""
	@echo "Compiling Minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC) -lreadline
	@echo "Minishell ready."

# Clean object files
clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH) --no-print-directory

# Clean everything
fclean: clean
	@echo "Removing Minishell..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH) --no-print-directory

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all re clean fclean
