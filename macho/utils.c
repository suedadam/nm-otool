/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:38:35 by asyed             #+#    #+#             */
/*   Updated: 2018/04/27 18:28:00 by asyed            ###   ########.fr       */
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
	// if (!ft_strcmp(sect, "__text"))
	// {
	// 	printf("sect = %s\n", sect);
	// 	return ('T');
	// }
	// if (!ft_strcmp(sect, "__bss"))
	// 	return ('B');
	// else if (!ft_strcmp(sect, "__common") || !ft_strcmp(sect, "__const") || !ft_strcmp(seg, "__TEXT"))
	// 	return ('S');
	// else if (!ft_strcmp(sect, "__data"))
	// 	return ('D');
	// else
	// {
	// 	printf("seg = %s sect = %s\n", seg, sect);
	// 	return ('?');
	// }
}

char	grab_typec(uint8_t type, uint8_t nsect)
{
	uint8_t	ntype;
	int		ext;

	ext = 32;
	if (type & N_EXT)
		ext = 0;
	ntype = type & N_TYPE;
	if (ntype == N_UNDF)
		return ('U' + ext);
	else if (ntype == N_ABS)
		return ('A' + ext);
	else if (ntype == N_SECT)
	{
		if (nsect & NO_SECT)
			return ('T' + ext);
		else
		{
			if (!g_sectnames[nsect])
				return ('T' + ext);
			// if (g_sectnames[nsect] == '?')
				// printf("nsect = %d\n",nsect );
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
