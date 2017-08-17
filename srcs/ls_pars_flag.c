/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pars_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 09:03:45 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/17 19:00:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ls_get_flag(t_env *e, char **argv, int i)
{
	int i_in;

	i_in = 1;
	while (argv[i][i_in])
	{
		if (argv[i][i_in] == 'l')
			e->flag |= FLAG_L;
		else if (argv[i][i_in] == 'R')
			e->flag |= FLAG_R;
		else if (argv[i][i_in] == 'a')
			e->flag |= FLAG_A;
		else if (argv[i][i_in] == 't')
			e->flag |= FLAG_T;
		else if (argv[i][i_in] == 'r')
			e->flag |= FLAG_RV;
		else if (argv[i][i_in] == 'd')
			e->flag |= FLAG_D;
		else if (argv[i][i_in] == 'U')
			e->flag |= FLAG_U;
		else if (argv[i][i_in] == 'S')
			e->flag |= FLAG_SS;
		else if (argv[i][i_in] != '1')
		{
			ft_dprintf(2, "ls: illegal option -- %c\n", argv[i][i_in]);
			ft_dprintf(2, "usage: ls [-RlartdU] [file ...]\n");
			return (0);
		}
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
