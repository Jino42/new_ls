/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pars_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:59:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 03:23:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ls_pars_flag(t_env *e, char **argv, int i)
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
		else if (argv[i][i_in] != '1')
		{
			ft_dprintf(2, "ls: illegal option -- %c\n", argv[i][i_in]);
			ft_dprintf(2, "usage: ls [-Rlart] [file ...]\n");
			return (0);
		}
		i_in++;
	}
	return (1);
}

void		temp_dir(t_env *e)
{
	struct stat buff;

	stat(("."), &buff);
	ft_lstinsert(&e->dir, ls_dir_path_to_lst("."));
}

int		ls_pars_files(t_env *e, char **argv, int i)
{
	t_elem *elem;
	struct stat buff;

	if (!argv[i])
		return (0);
	while (argv[i])
	{
		if (argv[i][0] == 0)
		{
			ft_putstr_fd("./ft_ls: fts_open: No such file or directory\n", 2); // LEAKS
			return (0);
		}
		if (!(stat(argv[i], &buff) == -1 && lstat(argv[i], &buff) == -1))
		{
			elem = ls_create_elem(buff, argv[i]);
			if (elem->mode[NUM_TYPE] == 'd')
				ft_lstinsert(&e->dir, ft_lstnew(argv[i], ft_strlen(argv[i]) + 1));//adddir
			else
				btree_insert_infix_data(&e->file, elem, &diff_alphabet);
		}
		else
			ft_lstinsert(&e->not_here, ft_lstnew(argv[i], ft_strlen(argv[i]) + 1));
		//Veirf si nb_arg++ dans ce cas
		e->nb_arg++;
		i++;
	}
	return (1);
}

int			ls_pars_arg(t_env *e, int argc, char **argv)
{
	int i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		ls_pars_flag(e, argv, i);
		i++;
	}
	if (!(ls_pars_files(e, argv, i)))
		temp_dir(e);
	return (1);
}
