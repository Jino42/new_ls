/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 06:00:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/19 15:29:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void		ls_remove_current_dir(t_env *e)
{
	t_list *tmp;

	tmp = ft_lst_remove_index(&e->dir, 0);
	if (tmp)
	{
		free(tmp->content);
		free(tmp);
	}
}

int			ls_loop(t_env *e)
{
	while (e->dir)
	{
		if (e->cur_dir)
			ft_printf("\n");
		e->cur_dir++;
		if (!(ls_get_dir(e, (char *)e->dir->content)))
			return (0);
		if (e->file && e->flag & FLAG_R)
			btree_apply_infix_env(e, e->file, &ls_btree_verif_dir);
		ls_print(e);
		ls_remove_current_dir(e);
		ls_maj_dir(e);
		if (e->file)
			btree_apply_free(e->file, &ls_free_elem);
		e->file = NULL;
	}
	return (1);
}
