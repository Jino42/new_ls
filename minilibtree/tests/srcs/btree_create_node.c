/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 21:10:29 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/09 22:13:13 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_02(t_env *e)
{
	t_btree *tree;
	tree = NULL;
	t_test *test;
	test = test_create(4, 'A');
	tree = btree_create_node(test, NULL, NULL);
	test = NULL;

	test = test_create(1, 1);
	tree->left = btree_create_node(test, NULL, NULL);;
	if (tree && *((int*)tree->content) == 4 && tree->left && *((int*)tree->left->content) == 1)
		print_ok(e, MSG_CREATE_NODE);
	else
		print_ko(e, MSG_CREATE_NODE);
	free(tree->left->content);
	free(tree->left);
	free(tree->content);
	free(tree);
}

void	test_01_basic(t_env *e)
{
	t_btree *tree;
	t_test *test;
	test = test_create(4, 'A');
	tree = NULL;
	tree = btree_create_node(test, NULL, NULL);
	if (tree != NULL && tree->right == NULL && tree->left == NULL)
		print_ok(e, MSG_CREATE_NODE);
	else
		print_ko(e, MSG_CREATE_NODE);
	free(tree->content);
	free(tree);
}

void		test_btree_create_node(t_env *e)
{
	test_01_basic(e);
	test_02(e);
}
