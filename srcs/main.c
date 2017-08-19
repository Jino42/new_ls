/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/19 15:37:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_print_arg(t_env *e)
{
	if (e->not_here)
	{
		ls_print_not_here(e);
		ft_lstdelall(&e->not_here, &ls_free_path);
		e->not_here = NULL;
	}
	if (e->file)
	{
		ls_print(e);
		e->cur_dir++;
		btree_apply_free(e->file, &ls_free_elem);
		e->file = NULL;
	}
}

static int	ls_free_all(t_env *e)
{
	ft_lstdelall(&e->not_here, &ls_free_path);
	ft_lstdelall(&e->temp_dir, &ls_free_path);
	ft_lstdelall(&e->dir, &ls_free_path);
	btree_apply_free(e->file, &ls_free_elem);
	return (1);
}

int			main(int argc, char **argv)
{
	t_env	e;

	(void)argc;
	ft_bzero(&e, sizeof(t_env));
	if (!(ls_pars_arg(&e, argv)))
		return (ls_free_all(&e));
	ls_print_arg(&e);
	if (!(ls_loop(&e)))
		return (ls_free_all(&e));
	return (ls_free_all(&e));
}
