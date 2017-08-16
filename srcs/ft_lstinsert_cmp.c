/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_cmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 11:36:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 11:37:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init(t_list **lst, t_list **past, t_list **cur, t_list *new)
{
	*past = NULL;
	*cur = *lst;
	if (*lst == NULL)
		*lst = new;
}

void		ft_lstinsert_cmp(t_list **lst, t_list *new,
						int (*cmp)(void *, void *))
{
	t_list *past;
	t_list *cur;

	if (lst == NULL || new == NULL)
		return ;
	init(lst, &past, &cur, new);
	while (cur)
	{
		if (cmp((cur->content), (new->content)) > 0)
		{
			new->next = cur;
			if (past)
				past->next = new;
			else
				*lst = new;
			return ;
		}
		past = cur;
		cur = cur->next;
	}
	if (past)
		past->next = new;
}
