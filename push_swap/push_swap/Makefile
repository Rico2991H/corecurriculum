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

NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = push_swap.c push_swap_extra.c push_swap_utils.c commandslista.c commandslistb.c errorhandling.c listcreation.c sortnumbers.c ft_split.c
OBJ = $(SRC:.c=.o)
INCLUDES = -I .

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)
	
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
post_build_clean:
	@rm -f $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

