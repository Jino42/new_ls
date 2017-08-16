/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_single_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 00:15:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 00:50:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_single_item_01(t_env *e)
{
	t_btree	*tree;
	tree = NULL;
	t_test *test;
	test = NULL;
	test = test_create(1, 1);
	tree = btree_create_leaf(test);
	test = test_create(2, 2);
	btree_insert_right(tree, test);
	if (*((int*)btree_child_right(tree)->content) == 2)
		print_ok(e, "Insert right ");
	else
		print_ko(e, "Insert right ");
	test = test_create(3, 3);
	btree_insert_left(tree, test);
	if (*((int*)btree_child_left(tree)->content) == 3)
		print_ok(e, "Insert left ");
	else
		print_ko(e, "Insert left ");
	test = NULL;
	btree_insert_right(tree->left, test);
	if (!tree->left->right->content)
		print_ok(e, "Insert right null ");
	else
		print_ko(e, "Insert right null ");
	test = NULL;
	btree_insert_left(tree->left->content, test);
	if (!tree->left->left)
		print_ok(e, "Insert left null ");
	else
		print_ko(e, "Insert left null ");

/////////////////////////////////////////////////


	t_test *ptr;

	ptr = btree_delete_right(tree->left);
	if (!ptr)
		print_ok(e, "Delete right null ");
	else
		print_ko(e, "Delete right null ");

	ptr = btree_delete_left(tree->left);
	if (!ptr)
		print_ok(e, "Delete right null ");
	else
		print_ko(e, "Delete right null ");

	ptr = btree_delete_right(tree);
	if (*((int*)ptr) == 2)
		print_ok(e, "Delete right");
	else
		print_ko(e, "Delete right");

	ptr = btree_delete_left(tree);
	if (*((int*)ptr) == 3)
		print_ok(e, "Delete right");
	else
		print_ko(e, "Delete right");
}

void	test_btree_single_item(t_env *e)
{
	test_single_item_01(e);
}
