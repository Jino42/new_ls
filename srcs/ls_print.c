/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 08:35:12 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/18 14:15:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ls_condition_print(t_env *e, t_size_m *size_m)
{
	void *ptr;

	if (!e->cur_dir)
		return (1);
	if ((e->dir && e->cur_dir > 1) || e->nb_arg > 1)
		ft_printf("%s:\n", (char*)(e->dir->content));
	if (e->dir && !e->file)
	{
		ptr = opendir((char *)e->dir->content);
		if (!ptr)
			ft_dprintf(2, "ls: %s: Permission denied\n",
					(char *)e->dir->content);
		else
			closedir(ptr);
	}
	return (1);
}

void		btree_print(void *env, void *size_m, void *ptr_elem)
{
	t_elem	*elem;
	t_env	*e;

	elem = (t_elem*)ptr_elem;
	e = (t_env *)env;
	if (e->flag & FLAG_I)
		ft_printf("%*ld ", ((t_size_m*)size_m)->ino_max, elem->st_ino);
	if (e->flag & FLAG_L)
		ls_print_l(e, elem, (t_size_m*)size_m);
	else
		ls_print_basic(e, elem);
}

void		btree_apply_infix_print_ls(void *env, void *size_m, t_btree *node,
										void (*apply)(void*, void*, void*))
{
	if (btree_child_left(node))
		btree_apply_infix_print_ls(env, size_m, btree_child_left(node), apply);
	apply(env, size_m, node->content);
	if (btree_child_right(node))
		btree_apply_infix_print_ls(env, size_m, btree_child_right(node), apply);
}

void		ls_print_not_here(t_env *e)
{
	t_list *l;

	l = e->not_here;
	while (l)
	{
		ft_dprintf(2, "ls: %s: No such file or directory\n",
						(char *)l->content);
		l = l->next;
	}
}

void		ls_print(t_env *e)
{
	t_elem		*elem;
	t_size_m	size_m;

	if (!(ls_condition_print(e, &size_m)))
		return ;
	if (!e->file)
		return ;
	ft_bzero(&size_m, sizeof(t_size_m));
	ls_max_print(e->file, &size_m);
	if (e->flag & FLAG_L && e->file && e->cur_dir)
		ft_printf("total %li\n", size_m.total_blocks);
	btree_apply_infix_print_ls((void *)e, (void *)&size_m,
												e->file, &btree_print);
}
