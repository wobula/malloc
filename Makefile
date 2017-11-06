# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschramm <rschramm@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 14:23:11 by rschramm          #+#    #+#              #
#    Updated: 2017/05/30 17:35:26 by rschramm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = malloc

CC = gcc

FLAG += -Wall -Werror -Wextra

SRC = src/main.c \

LIBFT = libft/libftprintf.a \

all: $(NAME)

$(NAME):
	cd libft && make re
	pwd
	gcc $(FLAG) -o $(NAME) ./src/main.c ./libft/libftprintf.a
	@echo "\033[33;32mSystem Ready >:D"

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "\033[33mCleaned..."

fclean:
	@make clean
	@make fclean -C libft
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "\033[31mfCleaned..."

re: fclean all
