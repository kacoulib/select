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

NAME = select

SRC = select.c

OBJDIR = objs

CFLAGS = -Wall -Wextra -Werror -g

DEP = lib/libft/libft.h

CC = gcc

OBJDIR = objs

OBJ = $(addprefix ${OBJDIR}/, $(SRC:.c=.o))

LIB = -L lib/libft

INCL = -I lib/libft

BY = "\033[33;1m"
BR = "\033[31;1m"
BG = "\033[32;1m"
BB = "\033[34;1m"
BM = "\033[35;1m"
BC = "\033[36;1m"
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
W = "\033[0m""\033[34;1m"
WR = "\033[0m""\033[31;5m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: libft ${NAME}

libft:
	@make -C lib/libft

${NAME}: ${OBJ}
	@${CC} ${CFLAGS} ${LIB} ${INCL} -o $@ ${OBJ}

${OBJDIR}/%.o: ./src/%.c ${DEP}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} ${INCL} -I. -c -o $@ $<
	@printf ${UP}${CUT}

clean:
	@make -C lib/libft/ clean
	@/bin/rm -Rf ${OBJDIR}

fclean: clean
	@make -C lib/libft/ fclean
	@/bin/rm -f ${NAME}

test:
	@${CC} -g -I./lib/libft/ -fsanitize=address ${LIB} \
	-I. -o ${NAME} $(addprefix src/, ${SRC})

debug: test
	lldb ./${NAME}

build: ${OBJ}

re: fclean all