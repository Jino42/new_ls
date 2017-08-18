/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat_insert_btree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 02:00:44 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/18 12:28:32 by ntoniolo         ###   ########.fr       */
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

static void		ls_stat_basic(t_env *e, t_elem *elem, struct stat buff)
{
	elem->size = buff.st_size;
	if (e->flag & FLAG_C)
		elem->time = buff.st_ctime;
	else if (e->flag & FLAG_T)
		elem->time = buff.st_mtime;
	else if (e->flag & FLAG_PU)
		elem->time = buff.st_atime;
	else
		elem->time = buff.st_mtime;
	elem->nlink = buff.st_nlink;
	elem->blocks = buff.st_blocks;
	elem->st_dev = buff.st_rdev;
	elem->st_ino = buff.st_ino;
}

t_elem			*ls_create_elem(t_env *e, struct stat buff, char *path)
{
	t_elem			*elem;
	struct passwd	*passwd;
	struct group	*group;

	passwd = NULL;
	group = NULL;
	if (!(elem = ft_memalloc(sizeof(t_elem))))
		exit(0);
	ft_memset(elem->mode, '-', sizeof(char) * 10);
	elem->path = path;
	ls_type_and_file_right(e, elem, buff.st_mode, &buff);
	elem->ind_last_slash = find_last_slash(elem);
	ls_stat_basic(e, elem, buff);
	passwd = getpwuid(buff.st_uid);
	group = getgrgid(buff.st_gid);
	if (passwd)
		elem->p_name = ft_strdup(passwd->pw_name);
	if (group)
		elem->g_name = ft_strdup(group->gr_name);
	return (elem);
}

t_btree			*ls_stat_create_leaf(t_env *e, struct stat buff, char *path)
{
	t_btree			*ret;

	ret = btree_create_leaf((void*)ls_create_elem(e, buff, path));
	return (ret);
}
