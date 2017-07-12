# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/11 14:44:42 by kacoulib          #+#    #+#              #
#    Updated: 2017/07/11 14:44:45 by kacoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  select
HEADERS	= select.h
LIBRARY	= -lncurses
SOURCES = src/select.c
OBJ	= $(SOURCES:.c=.o)
FLAGS	= -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
		gcc $(FLAGS) -c $(HEADERS) $(SOURCES)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)
clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
re : fclean all