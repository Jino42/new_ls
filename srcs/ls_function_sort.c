/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_function_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 08:05:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/18 12:23:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			cmp_elem_alphabet(void *s, void *s2)
{
	int		i;
	char	*str;
	char	*str2;

	str = ((t_elem*)s)->path;
	str2 = ((t_elem*)s2)->path;
	i = 0;
	while (str[i] && str2[i])
	{
		while (str[i] == '.' && str2[i] == '.')
			i++;
		if (str[i] != str2[i])
			return (str[i] - str2[i]);
		i++;
	}
	if (!str[i])
		return (-1);
	else if (!str2[i])
		return (1);
	return (0);
}

int			cmp_str_alphabet(void *s, void *s2)
{
	int		i;
	char	*str;
	char	*str2;

	str = (char *)s;
	str2 = (char *)s2;
	i = 0;
	while (str[i] && str2[i])
	{
		while (str[i] == '.' && str2[i] == '.')
			i++;
		if (str[i] != str2[i])
			return (str[i] - str2[i]);
		i++;
	}
	if (!str[i])
		return (-1);
	else if (!str2[i])
		return (1);
	return (0);
}

int			cmp_elem_time(void *node_elem, void *child_elem)
{
	t_elem *node;
	t_elem *child;

	node = (t_elem *)node_elem;
	child = (t_elem *)child_elem;
	if (node->time == child->time)
		return (cmp_str_alphabet(node->path, child->path));
	return ((node->time < child->time));
}

int			cmp_elem_size(void *node_elem, void *child_elem)
{
	t_elem *node;
	t_elem *child;

	node = (t_elem *)node_elem;
	child = (t_elem *)child_elem;
	if (node->size == child->size)
		return (cmp_str_alphabet(node->path, child->path));
	return ((node->size < child->size));
}

int			cmp_empty(void *node_elem, void *child_elem)
{
	(void)node_elem;
	(void)child_elem;
	return (1);
}
