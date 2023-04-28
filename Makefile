# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 15:23:50 by bbenidar          #+#    #+#              #
#    Updated: 2023/04/11 23:43:35 by bbenidar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk.a
CC	= gcc
FLAGS = -Wall -Wextra -Werror

SRC_C = util/ft_putstr.c util/string_h.c main.c

SRC_C_B = util/ft_putstr.c util/string_h.c bonus/client_bonus.c

SRC_S = util/ft_putstr.c util/string_h.c server.c 

SRC_S_B = util/ft_putstr.c util/string_h.c bonus/server_bonus.c

OBJ_C = ${SRC_C:.c=.o}

OBJ_C_B = ${SRC_C_B:.c=.o}

OBJ_S = ${SRC_S:.c=.o}

OBJ_S_B = ${SRC_S_B:.c=.o}

%.o : %.c minitalk.h
	${CC} ${FLAGS} -c $< -o $@
	
client: ${OBJ_C} server
	cc ${OBJ_C} -o $@

client_bonus: ${OBJ_C_B}
	cc ${OBJ_C_B} -o $@

server_bonus:  ${OBJ_S_B}
	cc ${OBJ_S_B} -o $@

server: ${OBJ_S}
	cc ${OBJ_S} -o $@

all:  client 

bonus: client_bonus server_bonus

fclean : clean
	rm -rf ${NAME}
	
clean :
	rm -rf ${OBJ_C} ${OBJ_C_B} ${OBJ_S} ${OBJ_S_B} client server server_bonus client_bonus
	
re	  : fclean all
