# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 09:15:00 by rhoogend          #+#    #+#              #
#    Updated: 2025/06/26 09:28:41 by rhoogend         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
MLX_DIR = minilibx-linux

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = libmlx_Linux.a
MLX_FLAGS = -L/usr/lib -lX11 -lXext -lm

SRC = main.c render.c initializer.c fractol_events.c fractol_utils.c fractols.c newtonbonus.c
OBJ = $(SRC:.c=.o)

INCLUDES = -I . -I $(LIBFT_DIR) -I$(MLX_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS)
	
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

