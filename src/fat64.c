/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:35:43 by asyed             #+#    #+#             */
/*   Updated: 2018/04/29 16:44:27 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_int.h"

static int	parse_fat_64(void *data, struct fat_arch_64 *fat)
{
	return (read_file(data + ntohl(fat->offset)));
}

int			fat_64(void *data)
{
	struct fat_header	*test;
	uint32_t			i;

	test = data;
	i = 0;
	while (htonl(i) < test->nfat_arch)
	{
		parse_fat_64(data, data +
			sizeof(struct fat_header) +
			(i * sizeof(struct fat_arch_64)));
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	parse_fat_64_swap(void *data, struct fat_arch_64 *fat)
{
	return (read_file(data + fat->offset));
}

int			fat_64_swap(void *data)
{
	struct fat_header	*test;
	uint32_t			i;

	test = data;
	i = 0;
	while (i < test->nfat_arch)
	{
		parse_fat_64_swap(data, data +
			sizeof(struct fat_header) +
			(i * sizeof(struct fat_arch_64)));
		i++;
	}
	return (EXIT_SUCCESS);
}
