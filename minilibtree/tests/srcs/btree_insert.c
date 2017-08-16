/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 02:01:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/11 03:12:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		cmp2(void *nb1, void *nb2)
{
	return (*((int*)nb1) - *((int*)nb2));
}

void	ft_putnbrtest2(void *ptr)
{
	ft_printf("%i ", *((int*)ptr));
}

void	test_btree_insert(t_env *e)
{
	t_btree	*root;
/*
	btree_apply_prefix(root, &ft_putnbrtest2);
	ft_printf("\n1 2 4 5 7 8 3 6 9\n\n");
	btree_apply_suffix(root, &ft_putnbrtest2);
	ft_printf("\n4 7 8 5 2 9 6 3 1\n\n");
	btree_apply_infix(root, &ft_putnbrtest2);
	ft_printf("\n4 2 7 5 8 1 3 9 6\n\n");
*/
	root = NULL;
	btree_insert_infix_data(&root, test_create(1, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(7, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(82, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(28, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(2, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(4, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(6, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(12, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(0, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(-4, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(-5, 1), &cmp2);
	btree_insert_infix_data(&root, test_create(5, 1), &cmp2);
	ft_printf("\033[33mPRINT RES_ INSERT_INFIX\n\033[0m");
	btree_apply_infix(root, &ft_putnbrtest2);
/*	t_btree **lst;
	t_btree *node;

	if (!(lst = ft_memalloc(sizeof(t_btree**) * btree_size(root))))
		exit(0);
	int i = 0;
	lst[i] = root;
	i++;
	while (i)
	{
		i--;
		node = lst[i];
		ft_printf("%i [%i]\n", i, *((int*)node->content));
		if (btree_child_left(node))
		{
			lst[i] = btree_child_left(node);
			i++;
		}
		if (btree_child_right(node))
		{
			lst[i] = btree_child_right(node);
			i++;
		}
	}

	if (btree_search_item(root, test_create(51, 14), &cmp2))
	{
		ft_printf("Ok");
	}*/
}
