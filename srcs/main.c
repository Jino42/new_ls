/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/17 15:43:13 by ntoniolo         ###   ########.fr       */
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

int			main(int argc, char **argv)
{
	t_env	e;

	ft_bzero(&e, sizeof(t_env));
	if (!(ls_pars_arg(&e, argc, argv))) //Need2Free
		return (1);
	ls_print_arg(&e);
	if (!(ls_loop(&e)))
		return (1);
	return (1);
}
