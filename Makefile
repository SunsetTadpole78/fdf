GREEN = \033[0;32m
YELLOW = \033[1;33m
ORANGE = \033[38;5;208m
RED = \033[0;31m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
CLEAR = \033[0m

CHECK = [✔ ]
CROSS = [✘]
ARROW = =>
INFO = [i]
SEPARATOR = "${CYAN}=====================================${CLEAR}"

SRC = src
INCLUDE = include

FDF = fdf

DEFAULT =	fdf.c

FILES = $(addprefix $(SRC)/, $(DEFAULT))

OBJS = $(FILES:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_INCLUDE_DIR = $(LIBFT_DIR)
LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = minilibx
MINILIBX_INCLUDE_DIR = $(MINILIBX_DIR)
MINILIBX = $(MINILIBX_DIR)/libmlx.a
MINILIBX_FLAGS = -lX11 -lXext -lm

all: $(FDF)

clean:
	@echo $(SEPARATOR)
	@echo "${RED}${CROSS} Cleaning object files...${CLEAR}"
	make -C $(LIBFT_DIR) clean > /dev/null
	make -C $(MINILIBX_DIR) clean > /dev/null
	rm -f $(OBJS)
	@echo "${GREEN}${CHECK} All object files cleaned successfully!${CLEAR}"	

fclean: clean
	@echo $(SEPARATOR)
	@echo "${RED}${CROSS} Removing executables...${CLEAR}"
	make -C $(LIBFT_DIR) fclean > /dev/null
	rm -f $(FDF)
	@echo "${GREEN}${CHECK} All executables and libraries removed successfully!${CLEAR}"

%.o: %.c
	@echo $(SEPARATOR)
	@echo "${ORANGE}${ARROW} Compiling ${YELLOW}$@${ORANGE}...${CLEAR}"
	gcc $(FLAGS) $< -c -o $@ -I $(INCLUDE) -I $(LIBFT_INCLUDE_DIR) -I $(MINILIBX_INCLUDE_DIR) $(MINILIBX_FLAGS) -g

$(FDF): $(LIBFT) $(MINILIBX) $(OBJS)
	@echo $(SEPARATOR)
	@echo "${ORANGE}${ARROW} Compiling ${YELLOW}${FDF}${ORANGE}...${CLEAR}"
	gcc $(FLAGS) $(OBJS) -o $(FDF) $(LIBFT) $(MINILIBX) -I $(INCLUDE) -I $(LIBFT_INCLUDE_DIR) -I $(MINILIBX_INCLUDE_DIR) $(MINILIBX_FLAGS) -g
	@echo "${GREEN}${CHECK} ${YELLOW}${FDF}${GREEN} compiled successfully!${CLEAR}"
	@echo $(SEPARATOR)
	@echo "${GREEN}${CHECK} All targets are up to date!${CLEAR}"

$(LIBFT):
	@echo $(SEPARATOR)
	@echo "${MAGENTA}${INFO} Building ${YELLOW}${LIBFT}${MAGENTA}...${CLEAR}"
	make -C $(LIBFT_DIR) bonus > /dev/null
	@echo "${GREEN}${CHECK} ${YELLOW}${LIBFT}${GREEN} built successfully!${CLEAR}"

$(MINILIBX):
	@echo $(SEPARATOR)
	@echo "${MAGENTA}${INFO} Building ${YELLOW}${MINILIBX}${MAGENTA}...${CLEAR}"
	make -C $(MINILIBX_DIR) > /dev/null
	@echo "${GREEN}${CHECK} ${YELLOW}${MINILIBX}${GREEN} built successfully!${CLEAR}"

re: fclean all

.PHONY: all clean fclean re
