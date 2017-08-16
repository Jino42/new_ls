/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_leaf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 22:07:07 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 00:10:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_other_03(t_env *e)
{
	t_btree	*tree;
	tree = NULL;
	t_test *test;
	test = NULL;
	if (!btree_size(tree))
		print_ok(e, "Size ");
	else
		print_ko(e, "Size ");
	test = test_create(1, 1);
	tree = btree_create_leaf(test);
	test = NULL;
	if (btree_size(tree) == 1)
		print_ok(e, "Size ");
	else
		print_ko(e, "Size ");
	tree->left = btree_create_leaf(test);
	tree->left->left = btree_create_leaf(test);
	tree->left->left->left = btree_create_leaf(test);
	tree->left->left->left->left = btree_create_leaf(test);
	tree->left->left->right = btree_create_leaf(test);
	tree->left->right = btree_create_leaf(test);
	if (btree_size(tree) == 7)
		print_ok(e, "Size ");
	else
		print_ko(e, "Size ");
	tree->right = btree_create_leaf(test);
	if (btree_size(tree) == 8)
		print_ok(e, "Size ");
	else
		print_ko(e, "Size ");
	tree->right->right = btree_create_leaf(test);
	tree->right->right->right = btree_create_leaf(test);
	tree->right->right->right->right = btree_create_leaf(test);
	tree->right->right->right->right->right = btree_create_leaf(test);
	if (btree_size(tree) == 12)
		print_ok(e, "Size ");
	else
		print_ko(e, "Size ");
	tree->right->left = btree_create_leaf(test);
	tree->right->left->left = btree_create_leaf(test);
	if (btree_size(tree) == 14)
		print_ok(e, "Size ");
	else
		print_ko(e, "Size ");

}

void	test_other_02(t_env *e)
{
	t_btree *tree;
	tree = NULL;
	t_test *test;
	test = test_create(4, 'A');
	tree = btree_create_node(test, NULL, NULL);
	test = NULL;

	test = test_create(1, 1);
	if (btree_is_leaf(tree))
		print_ok(e, "isLeaf");
	else
		print_ko(e, "isLeaf");
	tree->left = btree_create_node(test, NULL, NULL);;
	if (!btree_child_right(tree))
		print_ok(e, "child_right");
	else
		print_ko(e, "child_right");
	if (*((int*)btree_child_left(tree)->content) == 1)
		print_ok(e, "child_left");
	else
		print_ko(e, "child_left");
	free(tree->left->content);
	free(tree->left);
	free(tree->content);
	free(tree);
}

void	test_other_01(t_env *e)
{
	t_btree *tree;
	t_test *test;
	test = test_create(4, 'A');
	tree = NULL;
	if (btree_is_empty(tree))
		print_ok(e, "Empty");
	else
		print_ko(e, "Empty");
	tree = btree_create_leaf(test);
	if (!btree_is_empty(tree))
		print_ok(e, "Empty");
	else
		print_ko(e, "Empty");
	free(tree);
}

void		test_btree_other(t_env *e)
{
	test_other_01(e);
	test_other_02(e);
	test_other_03(e);
}
