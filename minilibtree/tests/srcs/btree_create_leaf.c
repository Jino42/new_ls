/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_leaf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 22:07:07 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/09 22:13:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_create_leaf_02(t_env *e)
{
	t_btree *tree;
	t_test *test;
	tree = NULL;
	tree = btree_create_leaf(test);
	if (tree != NULL && tree->content != NULL && tree->right == NULL && tree->left == NULL)
		print_ok(e, MSG_CREATE_LEAF);
	else
		print_ko(e, MSG_CREATE_LEAF);
	free(tree->content);
	free(tree);
}

void	test_create_leaf_01(t_env *e)
{
	t_btree *tree;
	t_test *test;
	test = test_create(4, 'A');
	tree = NULL;
	tree = btree_create_leaf(test);
	if (tree != NULL && tree->right == NULL && tree->left == NULL)
		print_ok(e, MSG_CREATE_LEAF);
	else
		print_ko(e, MSG_CREATE_LEAF);
	free(tree);
}

void		test_btree_create_leaf(t_env *e)
{
	test_create_leaf_01(e);
	test_create_leaf_02(e);
}
