# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/04 15:21:18 by otimofie          #+#    #+#              #
#    Updated: 2018/03/13 16:01:45 by otimofie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = otimofie.filler

LIB = filler.a

SRCS = main.c \
		main_1.c \
		main_2.c \
		main_3.c \
		main_4.c \
		main_5.c \

HEADER = filler.h

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRCS:.c=.o)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<
	
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C ./ft_printf
	gcc $(CFLAGS) -I. $(SRCS) -L ./ft_printf -lftprintf -o $(NAME)
	ar rc $(LIB) $(OBJECTS)
	ranlib $(LIB)

clean:
	/bin/rm -f $(OBJECTS)
	make clean -C ./ft_printf

fclean: clean
	/bin/rm -f $(NAME) $(LIB)
	make fclean -C ./ft_printf

re: fclean all

