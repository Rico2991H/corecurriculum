# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/24 13:46:52 by rhoogend          #+#    #+#              #
#    Updated: 2026/03/31 15:04:31 by rhoogend         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Polymorph
CXX = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = AMateria.cpp Character.cpp Cure.cpp Ice.cpp ICharacter.cpp\
	IMateriaSource.cpp Main.cpp MateriaSource.cpp

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