# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/09 10:40:06 by rhoogend          #+#    #+#              #
#    Updated: 2026/05/27 15:21:16 by fgreiff          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

##including Libft
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

##Including MLX
MLX_DIR = minilibx-linux
MLXFLAGS = -L/usr/lib -lX11 -lXext -lm
MLX = $(MLX_DIR)/libmlx_Linux.a 

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
MAP_DIR = maps
TXT_DIR = textures
GNL_DIR = $(SRC_DIR)/getnextline
MAPE_DIR = $(SRC_DIR)/mapparse
INIT_DIR = $(SRC_DIR)/initialization
CLEAN_DIR = $(SRC_DIR)/clean_up
MOVE_DIR = $(SRC_DIR)/movement
RAY_DIR = $(SRC_DIR)/raycasting
DRAW_DIR = $(SRC_DIR)/draw_pixels
ER_DIR = $(SRC_DIR)/errors
SRC = \
	$(SRC_DIR)/main.c $(GNL_DIR)/get_next_line_utils.c $(GNL_DIR)/get_next_line.c $(MAPE_DIR)/map_extract.c $(MAPE_DIR)/map_extract_checkers.c \
	$(MAPE_DIR)/validate_map.c $(MAPE_DIR)/validate_rgb.c $(MAPE_DIR)/rgb_atoi.c $(MAPE_DIR)/clean_textures.c $(MAPE_DIR)/extract_helpers.c\
	$(INIT_DIR)/init_window.c $(INIT_DIR)/render_loop.c $(INIT_DIR)/init_player.c $(CLEAN_DIR)/clean_up.c $(MOVE_DIR)/movements.c $(MOVE_DIR)/player_movement.c \
	$(INIT_DIR)/init_tiles.c  $(INIT_DIR)/init_rays.c $(RAY_DIR)/vert_inter.c $(RAY_DIR)/hor_inter.c $(RAY_DIR)/raycasting.c $(MOVE_DIR)/rotate_player.c\
	$(DRAW_DIR)/draw_game.c $(DRAW_DIR)/draw_mm.c $(INIT_DIR)/init_textures.c $(ER_DIR)/e_handling.c $(MAPE_DIR)/validate_textures.c

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT)  $(MLX) $(MLXFLAGS)

$(OBJ_DIR)/%.o:
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(filter %/$*.c,$(SRC)) -o $@

clean:
		rm -rf $(OBJ_DIR)
		$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
