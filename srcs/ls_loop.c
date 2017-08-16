/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 06:00:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 03:26:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*
** Add
** Add
** == inv
*/

void	print(void *env, void *ptr)
{
	t_elem *elem;
	t_env *e;

	e = (t_env*)env;
	elem = (t_elem*)ptr;
	if (e->flag & FLAG_R && elem->mode[NUM_TYPE] == 'd') // condition fonction useless without R ?
	{
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

void		ls_maj_dir(t_env *e)
{
	t_list *l;
	t_list *save;

	l = e->temp_dir;
	while (l)
	{
		save = l->next;
		ft_lstadd(&e->dir, l);
		l = save;
	}
	e->temp_dir = NULL;
}

int			ls_loop(t_env *e)
{
	while (e->dir)
	{
		if (e->cur_dir)
			ft_printf("\n");
		e->cur_dir++;
		ls_get_dir(e, (char *)e->dir->content);
		if (e->file)
			btree_apply_infix_env(e, e->file, &print);
		ls_print(e);
		ft_lst_remove_index(&e->dir, 0); // NEED TO FREE
		ls_maj_dir(e);
		e->file = NULL;
		e->not_here = NULL;
	}
	return (1);
}
