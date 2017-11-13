# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/30 12:55:46 by rschramm          #+#    #+#              #
#    Updated: 2017/11/08 12:36:21 by rschramm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

TESTNAME = malloc
TESTSRC = ./src/main.c

LIBFT = ./libft/libftprintf.a
LIBFTHEAD = -I ./libft/includes/

GCC = gcc
HEADERS = -I ./includes/
FLAGS += -Wall -Wextra -Werror
SRC = ./src/malloc.c \
	  ./src/realloc.c \
	  ./src/free.c \
	  ./src/allocate_node.c \
	  ./src/show_alloc_mem.c \
	  ./src/calloc.c \

COMPILE = $(GCC) $(FLAGS) $(SRC) $(HEADERS) $(LIBFTHEAD) $(LIBFT) -shared -o $(NAME) -g
TEST_MAIN = $(GCC) $(FLAGS) $(HEADERS) $(LINK) $(LIBFT) $(TESTSRC) -o $(TESTNAME) -g

OUTPUTBUILD = echo "\033[32mBuilding Malloc\033[0m"
OUTPUTCLEAN = echo "\033[31mRemoving Objects\033[0m"
OUTPUTFCLEAN = echo "\033[31mRemoving Executable\033[0m"
OUTPUTGO = echo "\033[92mSystem Ready :D\033[0m"
OUTPUTLIB = echo "\033[36;21mRebuilding Lib\033[0m"
OUTPUTRE = echo "\033[96;21mRebuilding Malloc\033[0m"

all: $(NAME)

$(NAME):
	@cd libft && make re
	@$(OUTPUTBUILD)
	@$(COMPILE)
	@/bin/rm -f $(LINK)
	@ln -s $(NAME) $(LINK)
	@$(TEST_MAIN)
	@$(OUTPUTGO)

clean:
	@$(OUTPUTCLEAN)
	@rm -f $(OBJ)

fclean: clean
	@$(OUTPUTFCLEAN)
	@rm -f $(NAME)
	@rm -f $(TESTNAME)

re:
	@$(OUTPUTRE)
	@make fclean
	@make

.PHONY: all clean fclean re
