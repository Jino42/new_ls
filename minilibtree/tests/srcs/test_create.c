/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 21:12:05 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/09 21:12:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_test		*test_create(int nb, char c)
{
	t_test *test;

	test = NULL;
	if (!(test = ft_memalloc(sizeof(t_test))))
		return (0);
	test->nb = nb;
	test->c = c;
	return (test);
}
