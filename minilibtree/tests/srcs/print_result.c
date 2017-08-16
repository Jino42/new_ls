/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 21:19:00 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/09 22:10:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void		print_ok(t_env *e, char *str)
{
	e->i++;
	ft_printf("\033[32m%s Test %3i OK\033[0m\n", str, e->i);
}

void		print_ko(t_env *e, char *str)
{
	e->i++;
	ft_printf("\033[31m%s Test %3i KO\033[0m\n", str, e->i);
}
