# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/08/11 02:12:22 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

FLAGS =

INC_FILES = includes/test.h

INC = includes/

SRC =	srcs/main.c \
		srcs/test_create.c \
		srcs/print_result.c \
		srcs/btree_create_node.c \
		srcs/btree_create_leaf.c \
		srcs/btree_other.c \
		srcs/btree_single_item.c \
		srcs/btree_apply.c \
		srcs/btree_insert.c \

OBJET = $(SRC:.c=.o)

.PHONY: all, clean, fclean, re, $(NAME)

all: $(NAME)

$(NAME): $(OBJET)
	@gcc -L ./../../libft/ -lft -L ./../ -lbtree $(OBJET) -I ./$(INC) -o $(NAME)
	@rm srcs/*.o

srcs/%.o: srcs/%.c
	@gcc $(FLAGS) -I ./$(INC) -o $@ -c $^

clean:
	@/bin/rm -f $(OBJET)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
