# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 14:58:42 by lroussel          #+#    #+#              #
#    Updated: 2025/02/04 12:22:51 by lroussel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

DEFAULT =	fdf.c		\
		views/isometric.c		\
		utils/templates/toggle.c		\
		utils/templates/keybox.c		\
		utils/navbar/navbar.c		\
		utils/navbar/default_color.c		\
		utils/button.c		\
		utils/resolution.c		\
		initialization/file_lines.c		\
		initialization/map.c		\
		initialization/display_data.c	\
		initialization/navbar.c	\
		initialization/controls.c	\
		initialization/backgrounds.c	\
		keys/hook.c	\
		keys/rotation_keys.c	\
		keys/translation_keys.c	\
		keys/zoom_keys.c	\
		destructor.c	\
		lines_utils.c	\
		mlx_manager.c	\
		utils.c		\
		color.c		\
		backgrounds.c		\
		depth_manager.c		\
		fix_line.c		\
		vector.c

FILES = $(addprefix $(SRC)/, $(DEFAULT))

OBJS = $(DEFAULT:%.c=obj/%.o)

FLAGS = -Wall -Wextra -Werror -O3

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
	rm -rf obj
	@echo "${GREEN}${CHECK} All object files cleaned successfully!${CLEAR}"	

fclean: clean
	@echo $(SEPARATOR)
	@echo "${RED}${CROSS} Removing executables...${CLEAR}"
	make -C $(LIBFT_DIR) fclean > /dev/null
	rm -f $(FDF)
	@echo "${GREEN}${CHECK} All executables and libraries removed successfully!${CLEAR}"

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	@echo $(SEPARATOR)
	@echo "${ORANGE}${ARROW} Compiling ${YELLOW}$@${ORANGE}...${CLEAR}"
	cc $(FLAGS) $< -c -o $@ -I $(INCLUDE) -I $(LIBFT_INCLUDE_DIR) -I $(MINILIBX_INCLUDE_DIR) $(MINILIBX_FLAGS)

$(FDF): $(LIBFT) $(MINILIBX) $(OBJS)
	@echo $(SEPARATOR)
	@echo "${ORANGE}${ARROW} Compiling ${YELLOW}${FDF}${ORANGE}...${CLEAR}"
	cc $(FLAGS) $(OBJS) -o $(FDF) $(LIBFT) $(MINILIBX) -I $(INCLUDE) -I $(LIBFT_INCLUDE_DIR) -I $(MINILIBX_INCLUDE_DIR) $(MINILIBX_FLAGS)
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
