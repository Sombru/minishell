NAME = libft

ARRAYS = arrays/
CONVERSION = conversion/
FDS = fds/
MEMORY = memory/
STRING = string/
TYPES = types/

FT_PRINTF = ft_printf/


SRCS =	$(ARRAYS)ft_arrcomb.c $(ARRAYS)ft_arrcpy.c $(ARRAYS)ft_arrstr_rm.c $(ARRAYS)ft_free_array.c \
		$(ARRAYS)ft_split.c $(ARRAYS)ft_count_args.c \
		$(CONVERSION)ft_atoi.c $(CONVERSION)ft_bzero.c $(CONVERSION)ft_itoa.c \
		$(CONVERSION)ft_rmlast_char.c $(CONVERSION)ft_rm_char.c $(CONVERSION)ft_stradd_start_end.c \
		$(CONVERSION)ft_tolower.c $(CONVERSION)ft_toupper.c $(CONVERSION)ft_swap.c $(CONVERSION)ft_xtoa.c\
		$(FDS)ft_putchar_fd.c $(FDS)ft_putstr_fd.c $(FDS)ft_putendl_fd.c $(FDS)ft_putnbr_fd.c \
		$(FDS)get_next_line.c $(FDS)gnl_smart.c \
		$(MEMORY)ft_memset.c  $(MEMORY)ft_memcpy.c $(MEMORY)ft_memmove.c \
		$(MEMORY)ft_memchr.c $(MEMORY)ft_memcmp.c $(MEMORY)ft_calloc.c $(MEMORY)ft_realloc.c \
		$(STRING)ft_strlen.c $(STRING)ft_strlcpy.c $(STRING)ft_strlcat.c  \
		$(STRING)ft_strchr.c $(STRING)ft_strrchr.c $(STRING)ft_strncmp.c \
		$(STRING)ft_strnstr.c $(STRING)ft_strdup.c $(STRING)ft_strcmp.c $(STRING)ft_substr.c \
		$(STRING)ft_strjoin.c $(STRING)ft_strtrim.c  $(STRING)ft_strmapi.c \
		$(STRING)ft_striteri.c $(STRING)ft_strjoin_free.c \
		$(STRING)ft_strncpy.c $(STRING)ft_strcpy.c $(STRING)ft_strcat.c $(STRING)ft_strndup.c \
		$(TYPES)ft_isalpha.c $(TYPES)ft_isdigit.c $(TYPES)ft_isalnum.c $(TYPES)ft_isascii.c \
		$(TYPES)ft_isprint.c \
		$(FT_PRINTF)ft_printf.c $(FT_PRINTF)debug.c $(FT_PRINTF)convert.c $(FT_PRINTF)parse_flags.c \
		$(FT_PRINTF)print_char.c $(FT_PRINTF)print_digit.c $(FT_PRINTF)print_hex.c $(FT_PRINTF)print_pointer.c $(FT_PRINTF)print_string.c \
		$(FT_PRINTF)print_unsigned.c 
		
OBJS = $(SRCS:%.c=.obj/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\nCreated libft $(NAME).a"
	@ ar rcs $(NAME).a $(OBJS) > /dev/null 2>&1

.obj/%.o: %.c
	@printf "\r\033[KCompiling $<..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files"
	@$(RM) .obj

fclean: clean
	@echo "Cleaning all generated files"
	@$(RM) $(NAME).a

re: fclean all

.PHONY: all clean fclean re