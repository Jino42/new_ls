# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/08/11 02:09:01 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libbtree.a

FLAGS = -Wall -Werror -Wextra -g

INC_FILES = includes/btree.h

INC = includes/

SRC = srcs/btree_create_node.c \
	  srcs/btree_create_leaf.c \
	  srcs/btree_child_left.c \
	  srcs/btree_child_right.c \
	  srcs/btree_is_leaf.c \
	  srcs/btree_is_empty.c \
	  srcs/btree_size.c \
	  srcs/btree_insert_right.c \
	  srcs/btree_insert_left.c \
	  srcs/btree_delete_right.c \
	  srcs/btree_delete_left.c \
	  srcs/btree_depth_insert_right.c \
	  srcs/btree_depth_insert_left.c \
	  srcs/btree_apply_prefix.c \
	  srcs/btree_apply_infix.c \
	  srcs/btree_apply_suffix.c \
	  srcs/btree_insert_data.c \
	  srcs/btree_search_item.c \
	  srcs/btree_insert_infix_data.c \

OBJET = $(SRC:.c=.o)

.PHONY: all, clean, fclean, re, $(NAME)

all: $(NAME)

$(NAME): $(INC_FILES) $(OBJET)
	@ar rc $(NAME) $(OBJET) && ranlib $(NAME)

%.o: %.c
	gcc $(FLAGS) -I ./$(INC) -o $@ -c $^

clean:
	@/bin/rm -f $(OBJET)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
