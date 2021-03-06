/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pars_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 09:03:45 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/19 14:59:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ls_get_flag(t_env *e, char **argv, int i)
{
	int		i_in;
	char	strf[NB_FLAGS];
	char	*ptr;

	ft_strcpy(strf, STR_FLAGS);
	i_in = 1;
	while (argv[i][i_in])
	{
		ptr = NULL;
		if (!(ptr = ft_strchr(strf, argv[i][i_in])))
		{
			ft_dprintf(2, "ls: illegal option -- %c\n", argv[i][i_in]);
			ft_dprintf(2, "usage: ls [-1RatrdUScuifAmp] [file ...]\n");
			return (0);
		}
		else
			e->flag |= (1 << (ptr - strf));
		i_in++;
	}
	return (1);
}

static void	ls_assign_ptr_fun(t_env *e)
{
	e->cmp = &cmp_elem_alphabet;
	e->cmp_str = &cmp_str_alphabet;
	if (e->flag & FLAG_U || e->flag & FLAG_F)
	{
		e->cmp = &cmp_empty;
		e->cmp_str = &cmp_empty;
	}
	if (e->flag & FLAG_BA)
		e->flag |= FLAG_A;
	if (e->flag & FLAG_F)
	{
		e->flag |= FLAG_A | FLAG_U;
		if (e->flag & FLAG_T)
			e->flag ^= FLAG_T;
		if (e->flag & FLAG_RV)
			e->flag ^= FLAG_RV;
	}
	if (e->flag & FLAG_M)
		if (e->flag & FLAG_L)
			e->flag ^= FLAG_L;
	if (e->flag & FLAG_C || e->flag & FLAG_PU || e->flag & FLAG_T)
		e->cmp = &cmp_elem_time;
	if (e->flag & FLAG_SS)
		e->cmp = &cmp_elem_size;
}

int			ls_pars_flag(t_env *e, char **argv, int *i)
{
	int option;

	option = 0;
	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1] != '\0' && !option)
	{
		if (!ft_strcmp(argv[*i], "--"))
		{
			if (!option)
				option = 1;
			else
				return (0);
		}
		else if (!ls_get_flag(e, argv, *i))
			return (0);
		(*i)++;
	}
	ls_assign_ptr_fun(e);
	return (1);
}
