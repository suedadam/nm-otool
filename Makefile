NAME = ft_nm
CFLAGS += -Wall -Werror -Wextra -g -fsanitize=address
INCLUDES = 	-I deps/libft/inc \
			-I inc
CC = gcc
LIBFT = libftprintf.a

################################################################################
# Source directories identifiers                                               #
################################################################################

SRCDIR = src/

OBJSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR), $(SRC)))

################################################################################
# COLOR                                                                        #
################################################################################

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RES = \033[0m


################################################################################
# EXECUTION SOURCE FILES                                                       #
################################################################################

SRC =	\
	fat32 \
	fat64 \
	flags \
	mach32_swap \
	macho32 \
	macho64 \
	macho64_swap \
	sort \
	utils \
	archivelib_64

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(OBJSRC)
	@ echo "$(YELLOW)Compiling program...$(RES)"
	$(CC) main.c $(CFLAGS) -L deps/libft -lftprintf $(MALLOC_PATH) $(INCLUDES) $(OBJSRC) -o $(NAME)
	# install_name_tool -change $(MALLOC) $(MALLOC_PATH) $(NAME)
	@ echo "$(GREEN)$(NAME) binary ready$(RES)"

$(LIBFT):
	make -C deps/libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	/bin/rm -f $(OBJSRC)
	make -C deps/libft clean
	@ echo "$(RED)Cleaning folders of object files...$(RES)"

fclean: clean
	/bin/rm -f $(NAME)
	make -C deps/libft fclean
	@ echo "$(RED)Removing library file and binary...$(RES)"

re: fclean all
	@ echo "$(GREEN)Binary Remade$(RES)"
