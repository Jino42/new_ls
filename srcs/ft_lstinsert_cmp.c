/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_cmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 11:36:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/19 14:42:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		init(t_list **lst, t_list **past, t_list **cur, t_list *new)
{
	*past = NULL;
	*cur = *lst;
	if (*lst == NULL)
		*lst = new;
}

static void		ft_lstinsert_cmp(t_list **lst, t_list *new,
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

static void		ft_lstinsert_cmp_reverse(t_list **lst, t_list *new,
						int (*cmp)(void *, void *))
{
	t_list *past;
	t_list *cur;

	if (lst == NULL || new == NULL)
		return ;
	init(lst, &past, &cur, new);
	while (cur)
	{
		if (cmp((cur->content), (new->content)) < 0)
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

void			ft_lstinsert_dir(t_list **lst, t_list *new,
					int (*cmp)(void *, void *), int reverse)
{
	if (reverse)
		ft_lstinsert_cmp_reverse(lst, new, cmp);
	else
		ft_lstinsert_cmp(lst, new, cmp);
}
