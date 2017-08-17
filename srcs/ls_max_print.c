/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_max_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 20:11:10 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/17 17:12:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	count_nb(size_t nb)
{
	size_t i;

	i = 0;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static void		ls_set_max_print(t_size_m *size_m)
{
	size_m->size_max = count_nb(size_m->size_max);
	if (size_m->size_max == 0)
		size_m->size_max++;
	size_m->nlink_max = count_nb(size_m->nlink_max);
	size_m->minor_max = count_nb(size_m->minor_max);
	size_m->major_max = count_nb(size_m->major_max);
	if (size_m->nlink_max == 0)
		size_m->nlink_max++;
	if (size_m->major_max)
		size_m->major_max += 2;
	size_m->size_max += size_m->major_max + size_m->minor_max;
}

static void		ls_verif_max(void *ptr_size_m, void *ptr_elem)
{
	t_size_m	*size_m;
	t_elem		*elem;
	size_t		temp;

	size_m = (t_size_m*)ptr_size_m;
	elem = (t_elem*)ptr_elem;
	if (elem->size > size_m->size_max)
		size_m->size_max = elem->size;
	if (elem->nlink > size_m->nlink_max)
		size_m->nlink_max = elem->nlink;
	temp = ft_strlen(elem->p_name);
	if (temp > size_m->p_max)
		size_m->p_max = temp;
	temp = ft_strlen(elem->g_name);
	if (temp > size_m->g_max)
		size_m->g_max = temp;
	if (elem->mtime > MAX_YEARS)
		size_m->years_max = 1;
	if (((elem->st_dev >> 24) & 0xff) > size_m->major_max)
		size_m->major_max = ((elem->st_dev >> 24) & 0xff);
	if ((elem->st_dev & 0xff) > size_m->minor_max)
		size_m->minor_max = (elem->st_dev & 0xff);
	size_m->total_blocks += elem->blocks;
}

void			btree_apply_infix_max_print(void *size_m, t_btree *node,
										void (*apply)(void*, void*))
{
	if (btree_child_left(node))
		btree_apply_infix_max_print(size_m, btree_child_left(node), apply);
	apply(size_m, node->content);
	if (btree_child_right(node))
		btree_apply_infix_max_print(size_m, btree_child_right(node), apply);
}

void			ls_max_print(t_btree *root, t_size_m *size_m)
{
	btree_apply_infix_max_print((void *)size_m, root, &ls_verif_max);
	ls_set_max_print(size_m);
}
