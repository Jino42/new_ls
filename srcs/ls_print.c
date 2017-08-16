/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 08:35:12 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 08:48:48 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*ls_ret_time(t_elem *elem)
{
	char	*ret_time;
	time_t	cur;
	
	ret_time = NULL;
	ret_time = ctime((const time_t *)(&elem->mtime));
	cur = time(NULL);
	if (cur - elem->mtime > PRINT_DATE)
		ft_strcpy(&ret_time[11], &ret_time[19]);
	else if (cur - elem->mtime < 0)
		ft_strcpy(&ret_time[10], &ret_time[22]);
	return (ret_time);
}


static int	ls_condition_print(t_env *e, t_size_m *size_m)
{
	if (!e->cur_dir)
		return (1);
	if ((e->dir && e->cur_dir > 1) || e->nb_arg > 1)
		ft_printf("%s:\n", (char*)(e->dir->content));
	if (e->dir && !e->file)
	{
		void *ptr;
		ptr = opendir((char *)e->dir->content);
		if (!ptr)
			ft_dprintf(2, "ls: %s: Permission denied\n",
					(char *)e->dir->content);
		else
			closedir(ptr);
	}
	return (1);
}

void		ls_print_minor_major(t_elem *elem, t_size_m *size_m, char *ret_time)
{
	ft_printf("%*li, %*li %.*s %s",
			size_m->major_max, ((elem->st_dev >> 24) & 0xff),
			size_m->minor_max, (int)((elem->st_dev) & 0xff),
			12 + size_m->years_max, ret_time + 4,
			&elem->path[elem->ind_last_slash]);
}

void		ls_print_l(t_elem *elem, t_size_m *size_m)
{
	char	*ret_time;

	ret_time = ls_ret_time(elem);
	ft_printf("%s %*li %-*s  %-*s ",
			elem->mode,
			size_m->nlink_max + 1, elem->nlink,
			size_m->p_max, elem->p_name,
			size_m->g_max, elem->g_name);
	if (elem->mode[NUM_TYPE] == 'c' || elem->mode[NUM_TYPE] == 'b')
		ls_print_minor_major(elem, size_m, ret_time);
	else
	{
		ft_printf("%*li %.*s %s",
			size_m->size_max + 1, elem->size,
			12 + size_m->years_max, ret_time + 4,
			&elem->path[elem->ind_last_slash]);
	}
	if (elem->mode[NUM_TYPE] == 'l')
		ft_printf("%s", elem->r_lnk);
	ft_printf("\n");
}

void		ls_print_basic(t_elem *elem)
{
	ft_printf("%s\n", &elem->path[elem->ind_last_slash]);
}

void		btree_print(void *env, void *size_m, void *ptr_elem)
{
	t_elem *elem;
	t_env	*e;

	elem = (t_elem*)ptr_elem;
	e = (t_env *)env;
	if (e->flag & FLAG_L)
		ls_print_l(elem, (t_size_m*)size_m);
	else
		ls_print_basic(elem);
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
	//DO FREE HERE ?
}

void		ls_print(t_env *e)
{
	t_elem *elem;
	t_size_m	size_m;

	if (!(ls_condition_print(e, &size_m)))
		return ;
	if (!e->file)
		return ;
	ft_bzero(&size_m, sizeof(t_size_m)); // need to be useless
	ls_max_print(e->file, &size_m);
	if (e->flag & FLAG_L && e->file && e->cur_dir)
		ft_printf("total %li\n", size_m.total_blocks);
	btree_apply_infix_print_ls((void *)e, (void *)&size_m, e->file, &btree_print);
}
