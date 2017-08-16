/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 21:04:02 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/11 02:12:14 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../../includes/btree.h"

#define MSG_CREATE_NODE "btree_create_node :"
#define MSG_CREATE_LEAF "btree_create_leaf :"

typedef struct	s_test
{
	int			nb;
	char		c;
}				t_test;

typedef struct	s_env
{
	int			i;
}				t_env;

t_test      *test_create(int nb, char c);
void		test_btree_create_node(t_env *e);
void		test_btree_create_leaf(t_env *e);
void		test_btree_other(t_env *e);
void		test_btree_single_item(t_env *e);
void		test_btree_apply(t_env *e);
void		test_btree_insert(t_env *e);
void        print_ko(t_env *e, char *str);
void        print_ok(t_env *e, char *str);


#endif
