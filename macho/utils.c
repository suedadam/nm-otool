/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:38:35 by asyed             #+#    #+#             */
/*   Updated: 2018/04/27 19:02:03 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

char	ref_char(char *seg, char *sect)
{
	if (!ft_strcmp(sect, SECT_TEXT))
		return ('T');
	else if (!ft_strcmp(sect, SECT_DATA))
		return ('D');
	else if (!ft_strcmp(sect, SECT_BSS))
		return ('B');
	else if (!ft_strcmp(sect, SECT_COMMON))
		return ('C');
	else
		return ('S');
}

char	grab_typec(uint8_t type, uint8_t nsect)
{
	uint8_t	ntype;
	int		ext;

	ext = 32;
	if (type & N_EXT)
		ext = 0;
	ntype = type & N_TYPE;
	ntype &= ~N_EXT;
	// if (ntype == N_UNDF)
	// 	return ('U' + ext);
	if (ntype == N_ABS)
		return ('A' + ext);
	else if (ntype == N_SECT)
	{
		if (nsect & NO_SECT)
			return ('T' + ext);
		else
		{
			if (!g_sectnames[nsect])
				return ('T' + ext);
			return (g_sectnames[nsect] + ext);
		}
	}
	else if (ntype == N_PBUD)
		return ('P' + ext);
	else if (ntype == N_INDR)
		return ('I' + ext);
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
		(sym->addr) ? printf("%016llx ", sym->addr) : printf(EMPTYSPACES);
		printf("%c ", sym->typechar);
		printf("%s\n", sym->name);
		free(sym);
	}
	free(queue);
	return (EXIT_SUCCESS);
}
