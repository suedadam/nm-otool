/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:38:35 by asyed             #+#    #+#             */
/*   Updated: 2018/04/28 20:43:48 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

char	ref_char(__attribute__((unused)) char *seg, char *sect)
{
	if (!ft_strcmp(sect, SECT_TEXT))
		return ('T');
	else if (!ft_strcmp(sect, SECT_DATA))
		return ('D');
	else if (!ft_strcmp(sect, SECT_BSS))
		return ('B');
	else
		return ('S');
}

char	grab_typec(uint8_t type, uint8_t nsect, uint64_t value)
{
	int	ext;

	ext = 32;
	if (type & N_EXT)
		ext = 0;
	type &= ~N_EXT;
	if (type == N_UNDF && !value)
		return ('U' + ext);
	else if (type == N_UNDF)
		return ('C' + ext);
	else if (type == N_ABS)
		return ('A' + ext);
	else if (type == N_INDR)
		return ('I' + ext);
	else if (type == N_SECT)
	{
		if (!g_sectnames[nsect])
			return (' ');
		return (g_sectnames[nsect] + ext);
	}
	else
		return ('?');
}

int 	print_symbols(t_pqueue *queue)
{
	t_symsort	*sym;

	if (!queue)
		return (EXIT_FAILURE);
	while ((sym = ft_depqueue(queue)))
	{
		(sym->addr) ? ft_printf("%016llx ", sym->addr) : ft_printf(EMPTYSPACES);
		ft_printf("%c ", sym->typechar);
		ft_printf("%s\n", sym->name);
		free(sym);
	}
	free(queue);
	return (EXIT_SUCCESS);
}
