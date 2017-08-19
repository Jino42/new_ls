/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 07:28:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/19 15:33:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ls_is_p_pp(char *str)
{
	if (str[0] == '.' && str[1] == '\0')
		return (1);
	if (str[0] == '.' && str[1] == '.' && str[2] == '\0')
		return (1);
	return (0);
}

static int		ls_add_file_to_btree(t_env *e, char *path, struct dirent *dir)
{
	char			*temp;
	struct stat		buff;
	t_elem			*elem;

	temp = NULL;
	elem = NULL;
	if (!(e->flag & FLAG_A) && dir->d_name[0] == '.')
		return (-1);
	if (e->flag & FLAG_BA && ls_is_p_pp(dir->d_name))
		return (-1);
	e->nb_files++;
	temp = ft_sprintf("%s/%s", path, dir->d_name);
	if (!temp)
		return (0);
	if (!(stat(temp, &buff) == -1 && lstat(temp, &buff) == -1))
	{
		if (!(elem = ls_create_elem(e, buff, temp)))
			return (0);
		btree_insert_infix_data_ls(&e->file,
				elem, e->cmp, e->flag & FLAG_RV);
	}
	else
		free(temp);
	return (1);
}

int				ls_get_dir(t_env *e, char *path)
{
	void			*ptr;
	struct dirent	*dir;

	(void)e;
	e->nb_files = 0;
	e->index_files = 0;
	ptr = opendir(path);
	if (!ptr)
		return (-1);
	while ((dir = readdir(ptr)))
	{
		if (ls_add_file_to_btree(e, path, dir) == 0)
			return (0);
	}
	closedir(ptr);
	return (1);
}
