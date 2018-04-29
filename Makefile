NAME = ft_nm
OTOOLNAME = ft_otool
CFLAGS += -Wall -Werror -Wextra
INCLUDES = 	-I deps/libft/inc \
			-I inc
CLEANOBJS = 
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

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)


$(OTOOLNAME): CFLAGS += -DOTOOL
$(OTOOLNAME): $(CLEANOBJS) $(LIBFT) $(OBJSRC)
	@ echo "$(YELLOW)Compiling program...$(RES)"
	$(CC) main.c $(CFLAGS) -L deps/libft -lftprintf $(MALLOC_PATH) $(INCLUDES) $(OBJSRC) -o $(OTOOLNAME)
	@ echo "$(GREEN)$(OTOOLNAME) binary ready$(RES)"

$(NAME): $(CLEANOBJS) $(LIBFT) $(OBJSRC)
	@ echo "$(YELLOW)Compiling program...$(RES)"
	$(CC) main.c $(CFLAGS) -L deps/libft -lftprintf $(MALLOC_PATH) $(INCLUDES) $(OBJSRC) -o $(NAME)
	@ echo "$(GREEN)$(NAME) binary ready$(RES)"

$(LIBFT):
	make -C deps/libft

$(CLEANOBJS):
	/bin/rm -f $(OBJSRC)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean: $(CLEANOBJS)
	make -C deps/libft clean
	@ echo "$(RED)Cleaning folders of object files...$(RES)"

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(OTOOLNAME)
	make -C deps/libft fclean
	@ echo "$(RED)Removing library file and binary...$(RES)"

re: fclean all
	@ echo "$(GREEN)Binary Remade$(RES)"
