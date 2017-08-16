/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 01:25:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/14 02:11:54 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char *ft_strcar(char *dest, char *src)
{
	return ((*dest || (*src && (*dest = *src++))) ? ft_strcar(dest + 1, src) - 1 : dest);
}

int mpow(int nb, int pow)
{
	return ((pow > 1)? nb * mpow(nb, pow - 1): 1);
}

int	ft_atoil(char *p)
{
	return (*p ? (*p - 48) * mpow(10, ft_strlen(p)) + ft_atoil(p + 1): 0);
}

int main(int argc, char **argv)
{
	t_env e;

	ft_bzero(&e, sizeof(t_env));
	test_btree_create_node(&e);
	test_btree_create_leaf(&e);
	test_btree_other(&e);
	test_btree_single_item(&e);
	test_btree_apply(&e);
	test_btree_insert(&e);
	char *dest, *src;

	dest = ft_memalloc(20);
	src = ft_memalloc(20);
	ft_strcpy(dest, "slt ");
	ft_strcpy(src, " autre");
	ft_printf("%s%s\n", dest, src);
	ft_printf("[%s]\n", ft_strcar(dest, src));

	ft_printf("base %i\n", ft_atoil("123456"));
	ft_printf("\033[31matoi(%i)\033[0m\n", ft_atoil("-48"));
	return (0);
}
