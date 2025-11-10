# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 11:52:23 by rhoogend          #+#    #+#              #
#    Updated: 2025/11/05 13:58:52 by dmungunt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC_DIR = src
TKN_DIR = $(SRC_DIR)/tokenization
PRS_DIR = $(SRC_DIR)/parsing
EXP_DIR = $(SRC_DIR)/expansion
INC_DIR = includes

SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/history.c \
	$(SRC_DIR)/signal.c \
	$(TKN_DIR)/tokencounter.c \
	$(TKN_DIR)/tokenizer.c \
	$(PRS_DIR)/parsing.c $(PRS_DIR)/pars_red.c $(PRS_DIR)/parse_arg.c $(PRS_DIR)/parse_assign.c $(PRS_DIR)/parse_cmd.c $(PRS_DIR)/parse_op.c $(PRS_DIR)/recursion.c \
	$(EXP_DIR)/expansion.c
	
OBJ = $(SRC:.c=.o)

INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)
	
%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
