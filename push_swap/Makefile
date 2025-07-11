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

NAME = push_swap.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
PRINTF_DIR = ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
INCLUDES = -I . -I $(PRINTF_DIR)

SRC = push_swap.c commands.c

OBJ = $(SRC: .c=.o)

all: $(PRINTF) $(NAME)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR) all
	cp ${PRINTF} ${NAME}
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -C $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

