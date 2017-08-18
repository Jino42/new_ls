/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_fun_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:46:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/17 19:19:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		btree_insert_infix_data_ls(t_btree **root, void *item,
		int (*cmpf)(void *, void *), int reverse)
{
	if (!*root)
	{
		*root = btree_create_leaf(item);
		return ;
	}
	if (!reverse)
	{
		if (cmpf(item, (*root)->content) <= 0)
			btree_insert_infix_data_ls(&(*root)->left, item, cmpf, reverse);
		else
			btree_insert_infix_data_ls(&(*root)->right, item, cmpf, reverse);
	}
	else
	{
		if (cmpf(item, (*root)->content) > 0)
			btree_insert_infix_data_ls(&(*root)->left, item, cmpf, reverse);
		else
			btree_insert_infix_data_ls(&(*root)->right, item, cmpf, reverse);
	}
}
