# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/24 13:46:52 by rhoogend          #+#    #+#              #
#    Updated: 2026/03/19 16:12:47 by rhoogend         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = harlFilter
CXX = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = Harl.cpp Main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re