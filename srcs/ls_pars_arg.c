/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pars_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:59:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/19 15:37:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_add_current_dir(t_env *e)
{
	struct stat	buff;
	char		cur[2];
	t_elem		*elem;

	cur[0] = '.';
	cur[1] = '\0';
	stat(("."), &buff);
	if (!(e->flag & FLAG_D))
		ft_lstinsert(&e->dir, ft_lstnew(cur, 2));
	else
	{
		elem = ls_create_elem(e, buff, ft_strdup("."));
		elem->ind_last_slash = 0;
		btree_insert_infix_data_ls(&e->file, elem, e->cmp, e->flag & FLAG_RV);
	}
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

static void		ls_add_elem_arg(t_env *e, struct stat buff, char *argv)
{
	t_elem			*elem;

	if (buff.st_mode & S_IFDIR &&
				!(e->flag & FLAG_D || e->flag & FLAG_P))
		ft_lstinsert_dir(&e->dir, ft_lstnew(argv,
			ft_strlen(argv) + 1), e->cmp_str, e->flag & FLAG_RV);
	else
	{
		elem = ls_create_elem(e, buff, ft_strdup(argv));
		elem->ind_last_slash = 0;
		btree_insert_infix_data_ls(&e->file, elem, e->cmp,
											e->flag & FLAG_RV);
	}
}

static int		ls_pars_files(t_env *e, char **argv, int i)
{
	struct stat		buff;

	while (argv[i])
	{
		if (!(ls_empty_arg(argv, i)))
			return (0);
		if (!(stat(argv[i], &buff) == -1 && lstat(argv[i], &buff) == -1))
			ls_add_elem_arg(e, buff, argv[i]);
		else
			ft_lstinsert_dir(&e->not_here, ft_lstnew(argv[i],
					ft_strlen(argv[i]) + 1), &cmp_str_alphabet, 0);
		e->nb_arg++;
		i++;
	}
	return (1);
}

int				ls_pars_arg(t_env *e, char **argv)
{
	int i;

	i = 1;
	if (!(ls_pars_flag(e, argv, &i)))
		return (0);
	if (!argv[i])
		ls_add_current_dir(e);
	else if (!(ls_pars_files(e, argv, i)))
		return (0);
	return (1);
}
