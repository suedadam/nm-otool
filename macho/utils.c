/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:38:35 by asyed             #+#    #+#             */
/*   Updated: 2018/04/26 15:40:25 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

char	ref_char(char *seg, char *sect)
{
	if (!ft_strcmp(seg, "__TEXT"))
		return ('T');
	if (!ft_strcmp(sect, "__bss"))
		return ('b');
	else if (!ft_strcmp(sect, "__common"))
		return ('S');
	else if (!ft_strcmp(sect, "__data"))
		return ('D');
	else
		return ('?');
}

char	grab_typec(uint8_t type, uint8_t nsect)
{
	uint8_t	ntype;

		// // ntype = ptr->n_type;
		// if (type & N_STAB)
		// 	return ('-');
	ntype = type & N_TYPE;
	if (ntype == N_UNDF)
		return ('U');
	else if (ntype == N_ABS)
		return ('A');
	else if (ntype == N_SECT)
	{
		if (nsect & NO_SECT)
			return ('t');
		else
		{
			if (!g_sectnames[nsect])
				return ('T');
			return (g_sectnames[nsect]);
		}
	}
	else if (ntype == N_PBUD)
		return ('P');
	else if (ntype == N_INDR)
		return ('I');
	else
		return ('?');
}