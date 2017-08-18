/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/18 15:45:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/ft_printf.h"
# include "../minilibtree/includes/btree.h"
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

# define NUM_TYPE 0
# define NUM_USR 1
# define NUM_GRP 4
# define NUM_OTH 7
# define NUM_R 0
# define NUM_W 1
# define NUM_X 2
# define ALL_R 7894898

# define MAX_YEARS 253375970400
# define PRINT_DATE 15778800

# define NB_FLAGS 16
# define STR_FLAGS "1lRartdUScuifAmp"

# define FLAG_ONE (1 << 0)
# define FLAG_L (1 << 1)
# define FLAG_R (1 << 2)
# define FLAG_A (1 << 3)
# define FLAG_RV (1 << 4)
# define FLAG_T (1 << 5)
# define FLAG_D (1 << 6)
# define FLAG_U (1 << 7)
# define FLAG_SS (1 << 8)
# define FLAG_C (1 << 9)
# define FLAG_PU (1 << 10)
# define FLAG_I (1 << 11)
# define FLAG_F (1 << 12)
# define FLAG_BA (1 << 13)
# define FLAG_M (1 << 14)
# define FLAG_P (1 << 15)

# define P_FILE 0
# define P_DIR 1

typedef struct	s_size_m
{
	size_t p_max;
	size_t g_max;
	size_t size_max;
	size_t nlink_max;
	size_t years_max;
	size_t total_blocks;
	size_t minor_max;
	size_t major_max;
	size_t ino_max;
}				t_size_m;

typedef struct	s_elem
{
	long		st_ino;
	char		right;
	char		*path;
	char		mode[11];
	size_t		ind_last_slash;
	size_t		size;
	time_t		time;
	size_t		nlink;
	size_t		blocks;
	char		*p_name;
	char		*g_name;
	char		*r_lnk;
	dev_t		st_dev;
}				t_elem;

typedef struct	s_env
{
	int			flag;
	int			a;
	int			nb_arg;
	int			nb_files;
	int			index_files;
	int			cur_dir;
	int			(*cmp)(void *, void *);
	int			(*cmp_str)(void *, void *);
	t_btree		*file;
	t_list		*dir;
	t_list		*temp_dir;
	t_list		*not_here;
}				t_env;

void			ls_btree_verif_dir(void *env, void *ptr);
void			btree_apply_infix_env(void *env, t_btree *node, void (*apply)(void *, void *));

int				ls_pars_flag(t_env *e, char **argv, int *i);
int				ls_pars_arg(t_env *e, int argc, char **argv);

void			ls_print(t_env *e);
void			ls_print_l(t_env *e, t_elem *elem, t_size_m *size_m);
void			ls_print_basic(t_env *e, t_elem *elem);
void			ls_print_not_here(t_env *e);

int				cmp_elem_alphabet(void *s, void *s2);
int				cmp_elem_time(void *node, void *child);
int				cmp_elem_size(void *node, void *child);
int				cmp_str_alphabet(void *s, void *s2);
int				cmp_empty(void *a, void *b);
int				cmp_empty_reverse(void *a, void *b);

void			ls_max_print(t_btree *root, t_size_m *size_m);

void			ft_lstinsert_dir(t_list **list, t_list *new, int (*cmp)(void *, void *), int reverse);
t_list			*ft_lst_remove_index(t_list **lst, size_t index);

t_btree			*ls_stat_create_leaf(t_env *e, struct stat buff, char *path);
void			ls_type_and_file_right(t_env *e, t_elem *elem, ssize_t st_mode,
		struct stat *ptr_buff);
int				ls_get_dir(t_env *e, char *path);
t_elem			*ls_create_elem(t_env *e, struct stat buff, char *path);
int				ls_loop(t_env *e);

void			ls_free_elem(void *ptr_elem);
void			ls_free_path(void *path, size_t size);
void			ft_lstdelall(t_list **lst, void (*apply)(void *, size_t));

void        btree_insert_infix_data_ls(t_btree **root, void *item,
		int (*cmpf)(void *, void *), int reverse);

#endif
