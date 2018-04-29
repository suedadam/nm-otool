/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:35:43 by asyed             #+#    #+#             */
/*   Updated: 2018/04/28 17:01:33 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

int					parse_fat(void *data, struct fat_arch *fat)
{
	return (read_file(data + ntohl(fat->offset)));
}

int					fat_32(void *data)
{
	struct fat_header	*test;
	uint32_t			i;

	test = data;
	i = 0;
	while (htonl(i) < test->nfat_arch)
	{
		parse_fat(data, data + sizeof(struct fat_header) + (i * sizeof(struct fat_arch)));
		i++;
	}
	return (EXIT_SUCCESS);
}

int					fat_32_swap(void *data)
{
	return (read_file(data + sizeof(struct fat_header)));
}
