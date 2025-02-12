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
		drawers/axes.c	\
		drawers/background.c	\
		drawers/map.c	\
		drawers/line.c	\
		views/isometric.c		\
		views/parallel.c		\
		views/conic.c		\
		views/switcher.c		\
		utils/templates/cube.c		\
		utils/templates/toggle.c		\
		utils/templates/keybox.c		\
		utils/templates/square.c		\
		utils/templates/circle.c		\
		utils/navbar/navbar.c		\
		utils/navbar/drawer.c		\
		utils/navbar/category.c		\
		utils/navbar/subcategory.c		\
		utils/navbar/text.c		\
		utils/navbar/buttons.c		\
		utils/navbar/selection.c		\
		utils/navbar/register.c		\
		utils/default_color.c		\
		utils/buttons/button.c		\
		utils/buttons/drawer.c		\
		utils/buttons/set_data.c		\
		utils/resolution.c		\
		utils/pixel.c		\
		utils/image.c		\
		utils/controls/controls.c		\
		utils/controls/update.c		\
		utils/controls/keys.c		\
		utils/cosmetic/lines/lines1.c		\
		utils/cosmetic/lines/lines2.c		\
		utils/cosmetic/backgrounds/backgrounds1.c		\
		utils/cosmetic/backgrounds/backgrounds3.c		\
		utils/cosmetic/backgrounds/backgrounds2.c		\
		initialization/backgrounds.c				\
		initialization/file_lines.c		\
		initialization/map.c		\
		initialization/navbar/navbar.c	\
		initialization/navbar/cosmetic.c	\
		initialization/navbar/controls.c	\
		initialization/navbar/other.c	\
		initialization/views/isometric.c	\
		initialization/views/conic.c	\
		initialization/views/parallel.c	\
		initialization/data.c	\
		events/isometric/press.c	\
		events/conic/press.c	\
		events/parallel/press.c	\
		events/events.c	\
		events/controls_events.c	\
		events/navbar_events.c	\
		destructor.c	\
		utils/color.c		\
		utils/updater.c		\
		depth_manager.c		\
		utils/cohen_sutherland_clip.c

FILES = $(addprefix $(SRC)/, $(DEFAULT))

OBJS = $(DEFAULT:%.c=obj/%.o)

FLAGS = -Wall -Wextra -Werror -O3 -g -D WINDOW_SIZE=$(SIZE)

LIBFT_DIR = libft
LIBFT_INCLUDE_DIR = $(LIBFT_DIR)
LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = minilibx
MINILIBX_INCLUDE_DIR = $(MINILIBX_DIR)
MINILIBX = $(MINILIBX_DIR)/libmlx.a
MINILIBX_FLAGS = -lX11 -lXext -lm

SIZE ?= 1

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
	cc $(FLAGS) $< -c -o $@ -I $(INCLUDE) -I $(LIBFT_INCLUDE_DIR) -I $(MINILIBX_INCLUDE_DIR)

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
