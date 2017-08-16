/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 02:01:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 05:00:04 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		cmp(void *nb1, void *nb2)
{
	return (*((int*)nb1) - *((int*)nb2));
}

void	ft_putnbrtest(void *ptr)
{
	ft_printf("%i ", *((int*)ptr));
}

void	test_btree_apply(t_env *e)
{
	t_btree	*root;

	root = btree_create_leaf(test_create(1, 1));
	root->left = btree_create_leaf(test_create(2, 2));
	root->right = btree_create_leaf(test_create(3, 3));
	root->left->left = btree_create_leaf(test_create(4, 4));
	root->left->right = btree_create_leaf(test_create(5, 5));
	root->right->right = btree_create_leaf(test_create(6, 6));
	root->left->right->left = btree_create_leaf(test_create(7, 7));
	root->left->right->right = btree_create_leaf(test_create(8, 8));
	root->right->right->left = btree_create_leaf(test_create(9, 9));

	btree_apply_prefix(root, &ft_putnbrtest);
	ft_printf("\n1 2 4 5 7 8 3 6 9\n\n");
	btree_apply_suffix(root, &ft_putnbrtest);
	ft_printf("\n4 7 8 5 2 9 6 3 1\n\n");
	btree_apply_infix(root, &ft_putnbrtest);
	ft_printf("\n4 2 7 5 8 1 3 9 6\n\n");

	root = NULL;
	btree_insert_data(&root, test_create(1, 1), &cmp);
	btree_insert_data(&root, test_create(9, 1), &cmp);
	btree_insert_data(&root, test_create(4, 1), &cmp);
	btree_insert_data(&root, test_create(2, 1), &cmp);
	btree_insert_data(&root, test_create(10, 1), &cmp);
	btree_insert_data(&root, test_create(14, 1), &cmp);
	btree_insert_data(&root, test_create(51, 1), &cmp);
	btree_insert_data(&root, test_create(5, 1), &cmp);
	btree_insert_data(&root, test_create(18, 1), &cmp);
	//btree_apply_prefix(root, &ft_putnbrtest);
	t_btree **lst;
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

	if (btree_search_item(root, test_create(51, 14), &cmp))
	{
		ft_printf("Ok");
	}
}
