/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:36:01 by asyed             #+#    #+#             */
/*   Updated: 2018/04/29 16:44:11 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_int.h"

int		alpha_sort(t_symsort *old, t_symsort *new)
{
	if (!old || !new)
		return (1);
	if (ft_strcmp(old->name, new->name) > 0)
		return (0);
	return (1);
}

int		rev_alpha_sort(t_symsort *old, t_symsort *new)
{
	if (!old || !new)
		return (1);
	if (ft_strcmp(old->name, new->name) < 0)
		return (0);
	return (1);
}

int		addr_sort(t_symsort *old, t_symsort *new)
{
	if (!old || !new)
		return (1);
	if (old->addr > new->addr)
		return (0);
	return (1);
}

int		pick_sort(char c)
{
	if (c == 'r')
		g_sym_sort = &rev_alpha_sort;
	else if (c == 'n')
		g_sym_sort = &addr_sort;
	else
		g_sym_sort = &alpha_sort;
	return (EXIT_SUCCESS);
}
