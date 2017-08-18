/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pars_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 09:03:45 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/18 15:46:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ls_get_flag(t_env *e, char **argv, int i)
{
	int i_in;
	char strf[NB_FLAGS];
	char *ptr;

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
	return (1);
}
