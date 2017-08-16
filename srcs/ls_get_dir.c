/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 07:28:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 08:49:57 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ls_add_file_to_btree(t_env *e, char *path, struct dirent *dir)
{
	char			*temp;
	struct stat		buff;

	if (!(e->flag & FLAG_A) && dir->d_name[0] == '.')
		return (0);
	temp = ft_sprintf("%s/%s", path, dir->d_name);
	if (!(stat(temp, &buff) == -1 && lstat(temp, &buff) == -1))
		btree_insert_infix_data(&e->file,
			ls_create_elem(buff, temp), e->cmp);
	return (1);
}

int				ls_get_dir(t_env *e, char *path)
{
	void			*ptr;
	struct dirent	*dir;

	(void)e;
	ptr = opendir(path);
	if (!ptr)
		return (0);
	while ((dir = readdir(ptr)))
		ls_add_file_to_btree(e, path, dir);
	closedir(ptr);
	return (1);
}
