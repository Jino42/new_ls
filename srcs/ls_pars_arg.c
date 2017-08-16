/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pars_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:59:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 08:47:47 by ntoniolo         ###   ########.fr       */
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
			if (buff.st_mode & S_IFDIR)
				ft_lstinsert_cmp(&e->dir, ft_lstnew(argv[i], ft_strlen(argv[i]) + 1), e->cmp_str);
			else
				btree_insert_infix_data(&e->file, elem, e->cmp);
		}
		else
			ft_lstinsert_cmp(&e->not_here, ft_lstnew(argv[i], ft_strlen(argv[i]) + 1), &cmp_str_alphabet);
		e->nb_arg++;
		i++;
	}
	return (1);
}

int			ls_pars_arg(t_env *e, int argc, char **argv)
{
	int i;
	int option;

	option = 0;
	i = 1;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] != '\0' && !option)
	{
		if (!ft_strcmp(argv[i], "--"))
		{
			if (!option)
				option = 1;
			else
				return (0);
		}
		else if (!ft_strcmp(argv[i], "---"))
			break ;
		else
		{
			if (!ls_pars_flag(e, argv, i))
				return (0);
		}
		i++;
	}
	if (e->flag & FLAG_RV)
	{
		e->cmp = &cmp_elem_alphabet_reverse;
		e->cmp_str = &cmp_str_alphabet_reverse;
	}
	else
	{
		e->cmp = &cmp_elem_alphabet;
		e->cmp_str = &cmp_str_alphabet;
	}
	if (!argv[i])
		temp_dir(e);
	else if (!(ls_pars_files(e, argv, i)))
		return (0);
	return (1);
}
