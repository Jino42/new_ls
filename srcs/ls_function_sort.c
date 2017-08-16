/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_function_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 08:05:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 08:33:53 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			cmp_elem_alphabet(void *s, void *s2)
{
	int	i;
	char *str;
	char *str2;

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

int			cmp_elem_alphabet_reverse(void *s, void *s2)
{
	int	i;
	char *str;
	char *str2;

	str = ((t_elem*)s)->path;
	str2 = ((t_elem*)s2)->path;
	i = 0;
	while (str[i] && str2[i])
	{
		while (str[i] == '.' && str2[i] == '.')
			i++;
		if (str[i] != str2[i])
			return (str2[i] - str[i]);
		i++;
	}
	if (!str2[i])
		return (-1);
	else if (!str[i])
		return (1);
	return (0);
}

int			cmp_str_alphabet(void *s, void *s2)
{
	int	i;
	char *str;
	char *str2;

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

int			cmp_str_alphabet_reverse(void *s, void *s2)
{
	int	i;
	char *str;
	char *str2;

	str = (char *)s;
	str2 = (char *)s2;
	i = 0;
	while (str2[i] && str[i])
	{
		while (str2[i] == '.' && str[i] == '.')
			i++;
		if (str2[i] != str[i])
			return (str2[i] - str[i]);
		i++;
	}
	if (!str2[i])
		return (-1);
	else if (!str[i])
		return (1);
	return (0);
}