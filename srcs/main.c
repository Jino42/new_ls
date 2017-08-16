/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 03:28:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char **argv)
{
	t_env	e;

	ft_bzero(&e, sizeof(t_env));
	if (!(ls_pars_arg(&e, argc, argv)))
		return (1);
	if (e.not_here)
	{
		ls_print_not_here(&e);
		e.not_here = NULL;
	}
	if (e.file)
	{
		ls_print(&e);
		e.cur_dir++;
		e.file = NULL;
	}
	if (!(ls_loop(&e)))
		return (1);
	return (1);
}
