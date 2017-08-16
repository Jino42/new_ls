/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pars_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:59:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 09:11:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_add_current_dir(t_env *e)
{
	struct stat	buff;
	char		cur[2];

	cur[0] = '.';
	cur[1] = '\0';
	stat(("."), &buff);
	ft_lstinsert(&e->dir, ft_lstnew(cur, 2));
}

static int		ls_empty_arg(char **argv, int i)
{
	if (argv[i][0] == 0)
	{
		ft_putstr_fd("./ft_ls: fts_open: No such file or directory\n", 2);
		return (0);
	}
	return (1);
}

static int		ls_pars_files(t_env *e, char **argv, int i)
{
	t_elem			*elem;
	struct stat		buff;

	while (argv[i])
	{
		if (!(ls_empty_arg(argv, i)))
			return (0);
		if (!(stat(argv[i], &buff) == -1 && lstat(argv[i], &buff) == -1))
		{
			elem = ls_create_elem(buff, argv[i]);
			if (buff.st_mode & S_IFDIR)
				ft_lstinsert_cmp(&e->dir, ft_lstnew(argv[i],
							ft_strlen(argv[i]) + 1), e->cmp_str);
			else
				btree_insert_infix_data(&e->file, elem, e->cmp);
		}
		else
			ft_lstinsert_cmp(&e->not_here, ft_lstnew(argv[i],
						ft_strlen(argv[i]) + 1), &cmp_str_alphabet);
		e->nb_arg++;
		i++;
	}
	return (1);
}

void			ls_assign_ptr_fun(t_env *e)
{
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
}

int				ls_pars_arg(t_env *e, int argc, char **argv)
{
	int i;

	i = 1;
	if (!(ls_pars_flag(e, argv, &i)))
		return (0);
	ls_assign_ptr_fun(e);
	if (!argv[i])
		ls_add_current_dir(e);
	else if (!(ls_pars_files(e, argv, i)))
		return (0);
	return (1);
}
