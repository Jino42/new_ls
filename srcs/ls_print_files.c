/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 17:10:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/18 12:24:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*ls_ret_time(t_env *e, t_elem *elem)
{
	char	*ret_time;
	time_t	cur;

	ret_time = NULL;
	cur = time(NULL);
	ret_time = ctime((const time_t *)(&elem->time));
	if (cur - elem->time > PRINT_DATE)
		ft_strcpy(&ret_time[11], &ret_time[19]);
	else if (cur - elem->time < 0)
		ft_strcpy(&ret_time[10], &ret_time[22]);
	return (ret_time);
}

void		ls_print_minor_major(t_env *e, t_elem *elem, t_size_m *size_m,
										char *ret_time)
{
	ft_printf("%*li, %*li %.*s %s",
			size_m->major_max, ((elem->st_dev >> 24) & 0xff),
			size_m->minor_max, (int)((elem->st_dev) & 0xff),
			12 + size_m->years_max, ret_time + 4,
			&elem->path[elem->ind_last_slash]);
}

void		ls_print_l(t_env *e, t_elem *elem, t_size_m *size_m)
{
	char	*ret_time;

	ret_time = ls_ret_time(e, elem);
	ft_printf("%s %*li %-*s  %-*s ",
			elem->mode,
			size_m->nlink_max + 1, elem->nlink,
			size_m->p_max, elem->p_name,
			size_m->g_max, elem->g_name);
	if (elem->mode[NUM_TYPE] == 'c' || elem->mode[NUM_TYPE] == 'b')
		ls_print_minor_major(e, elem, size_m, ret_time);
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

void		ls_print_basic(t_env *e, t_elem *elem)
{
	(void)e;
	ft_printf("%s\n", &elem->path[elem->ind_last_slash]);
}
