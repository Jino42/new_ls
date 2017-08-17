/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_function_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 14:34:38 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/17 14:35:18 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_free_elem(void *ptr_elem)
{
	t_elem *elem;

	elem = (t_elem *)ptr_elem;
	if (elem)
	{
		ft_strdel(&elem->path);
		ft_strdel(&elem->g_name);
		ft_strdel(&elem->p_name);
		ft_strdel(&elem->r_lnk);
		free(elem);
	}
}

void		ls_free_path(void *content, size_t size)
{
	(void)size;

	if (content)
		ft_strdel((char **)&content);
}

void		ft_lstdelall(t_list **lst, void (*apply)(void *, size_t))
{
	t_list *tmp;
	t_list *l;

	l = *lst;
	while (l)
	{
		tmp = l;
		l = l->next;
		apply(tmp->content, tmp->content_size);
		free(tmp);
	}
	*lst = NULL;
}
