NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft/includes
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = srcs

SRCS = $(SRC_DIR)/pipex.c \
		$(SRC_DIR)/utils.c

SRCS_BONUS = $(SRC_DIR)/pipex_bonus.c \
		$(SRC_DIR)/utils_bonus.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRC_DIR)/%.c=%.o)

HEADER = includes/pipex.h

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus : $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME)

%.o: $(SRC_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f *.o
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean
