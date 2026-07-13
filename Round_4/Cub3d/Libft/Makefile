# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmungunt <dmungunt@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 10:27:03 by dmungunt          #+#    #+#              #
#    Updated: 2025/05/21 10:10:58 by dmungunt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
      ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
      ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
      ft_calloc.c ft_strdup.c ft_toupper.c ft_tolower.c \
      ft_strchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
      ft_strnstr.c ft_atoi.c ft_strrchr.c ft_substr.c \
      ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
      ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
      ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
	ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
	ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJECTS = ${SRC:.c=.o}
BONUS_OBJECTS = ${BONUS:.c=.o}

all: ${NAME}

${NAME}: ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}

bonus: ${OBJECTS} ${BONUS_OBJECTS}
	ar rcs ${NAME} ${OBJECTS} ${BONUS_OBJECTS}

.c.o:
	${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

clean:
	rm -f ${OBJECTS} ${BONUS_OBJECTS}

fclean: clean
	rm -f ${NAME}
	

re: fclean all
