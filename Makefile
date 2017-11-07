# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschramm <rschramm@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 14:23:11 by rschramm          #+#    #+#              #
#    Updated: 2017/11/06 09:08:46 by rschramm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = malloc

CC = gcc

FLAG += -Wall -Werror -Wextra

SRC = src/main.c \
		src/allocate_node.c \
		src/malloc.c \
		src/free.c \

LIBFT = libft/libftprintf.a \

all: $(NAME)

$(NAME):
	@gcc $(FLAG) -o $(NAME) $(SRC) $(LIBFT)
	@echo "\033[33;32mSystem Ready >:D"

clean:
	@rm -f $(OBJ)
	@echo "\033[33mCleaned..."

fclean: clean
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "\033[31mfCleaned..."

re:
	@cd ./libft && make re
	@make fclean
	@make all
