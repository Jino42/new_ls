/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_btree_verif_dir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 09:52:34 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 10:47:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_btree_verif_dir(void *env, void *ptr)
{
	t_elem *elem;
	t_env *e;

	e = (t_env*)env;
	elem = (t_elem*)ptr;
	if (elem->mode[NUM_TYPE] == 'd')
	{
		if (e->flag & FLAG_A)
		{
			if (!ft_strcmp(&elem->path[elem->ind_last_slash], ".") ||
					!ft_strcmp(&elem->path[elem->ind_last_slash], ".."))
				return ;
			else
				ft_lstadd(&e->temp_dir, ft_lstnew(elem->path, ft_strlen(elem->path) + 1));
		}
		else
			ft_lstadd(&e->temp_dir, ft_lstnew(elem->path, ft_strlen(elem->path) + 1));
	}
}

void	btree_apply_infix_env(void *env, t_btree *node, void (*apply)(void *, void *))
{
	if (btree_child_left(node))
		btree_apply_infix_env(env, btree_child_left(node), apply);
	apply(env, node->content);
	if (btree_child_right(node))
		btree_apply_infix_env(env, btree_child_right(node), apply);
}
