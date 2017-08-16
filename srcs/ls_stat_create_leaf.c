/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat_insert_btree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 02:00:44 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/15 11:27:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	find_last_slash(t_elem *elem)
{
	int i;

	i = ft_strlen(elem->path);
	while (i)
	{
		if (elem->path[i] == '/' && elem->path[i - 1] != '\\')
			return (i + 1);
		i--;
	}
	return (i);
}

static void		ls_stat_basic(t_elem *elem, struct stat buff)
{
	elem->size = buff.st_size;
	elem->atime = buff.st_atime;
	elem->ctime = buff.st_ctime;
	elem->mtime = buff.st_mtime;
	elem->nlink = buff.st_nlink;
	elem->blocks = buff.st_blocks;
	elem->st_dev = buff.st_rdev;
}

t_elem			*ls_create_elem(struct stat buff, char *path)
{
	t_elem			*elem;
	struct passwd	*passwd;
	struct group	*group;

	passwd = NULL;
	group = NULL;
	if (!(elem = ft_memalloc(sizeof(t_elem))))
			exit(0);
	ft_memset(elem->mode, '-', sizeof(char) * 10); //lastChar
	elem->path = path;
	ls_type_and_file_right(elem, buff.st_mode, &buff);
	elem->ind_last_slash = find_last_slash(elem);
	ls_stat_basic(elem, buff);
	passwd = getpwuid(buff.st_uid);
	group = getgrgid(buff.st_gid);
	if (passwd)
		elem->p_name = ft_strdup(passwd->pw_name); //or ptr
	if (group)
		elem->g_name = ft_strdup(group->gr_name); //or ptr
	return (elem);
}

t_btree			*ls_stat_create_leaf(t_env *e, struct stat buff, char *path)
{
	t_btree			*ret;

	ret = btree_create_leaf((void*)ls_create_elem(buff, path));
	return (ret);
}
