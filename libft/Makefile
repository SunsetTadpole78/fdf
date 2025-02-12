DEFAULT = ft_isalpha.c			\
	ft_isdigit.c			\
	ft_isdigit_str.c		\
	ft_isalnum.c			\
	ft_isascii.c			\
	ft_isprint.c			\
	ft_strlen.c			\
	ft_memset.c 			\
	ft_bzero.c  			\
	ft_memcpy.c 			\
	ft_memmove.c			\
	ft_strlcpy.c			\
	ft_strlcat.c			\
	ft_toupper.c			\
	ft_tolower.c			\
	ft_strchr.c 			\
	ft_strrchr.c			\
	ft_strncmp.c			\
	ft_memchr.c			\
	ft_memcmp.c 			\
	ft_realloc.c 			\
	ft_strnstr.c			\
	ft_atoi.c			\
	ft_strdup.c 			\
	ft_calloc.c 			\
	ft_substr.c 			\
	ft_strjoin.c			\
	ft_strtrim.c			\
	ft_count_words.c		\
	ft_count_words_charset.c	\
	ft_get_first_word.c		\
	ft_split.c			\
	ft_split_charset.c		\
	ft_itoa.c			\
	ft_count_digits.c		\
	ft_strmapi.c			\
	ft_striteri.c			\
	ft_putchar_fd.c			\
	ft_putstr_fd.c			\
	ft_putendl_fd.c			\
	ft_putnbr_fd.c			\
	ft_islower.c			\
	ft_isupper.c			\
	gnl/get_next_line.c		\
	gnl/get_next_line_utils.c	\
	ft_max.c	\
	ft_min.c	\
	ft_abs.c	\
	ft_angle.c	\
	ft_atof.c	\
	ft_atoh.c	\
	ft_distance.c	\
	ft_ftoi.c	\
	ft_ishexa.c	\
	ft_nextid.c	\
	ft_vector2.c	\
	ft_fromrgb.c	\
	ft_torgb.c	\
	ft_colorbetween.c
BONUS = ft_lstnew_bonus.c		\
	ft_lstadd_front_bonus.c		\
	ft_lstsize_bonus.c		\
	ft_lstlast_bonus.c		\
	ft_lstadd_back_bonus.c		\
	ft_lstdelone_bonus.c		\
	ft_lstclear_bonus.c		\
	ft_lstiter_bonus.c		\
	ft_lstmap_bonus.c		\
	ft_lstmax_bonus.c		\
	ft_lstmin_bonus.c

OBJS =  $(DEFAULT:%.c=%.o)
OBJS_A = $(OBJS) $(BONUS:%.c=%.o)
NAME = libft.a
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar cr $(NAME) $(OBJS)

bonus: $(OBJS_A)
	ar cr $(NAME) $(OBJS_A)

%.o: %.c
	gcc $(FLAGS) $< -c -o $@ -I .

clean:
	rm -f $(OBJS_A)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
