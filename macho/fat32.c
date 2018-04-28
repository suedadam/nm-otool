/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:35:43 by asyed             #+#    #+#             */
/*   Updated: 2018/04/27 18:30:27 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <mach-o/fat.h>

static int			parse_fat(void *data, struct fat_arch *fat)
{
	// printf("offset = %u\n", ntohl(fat->offset));
	// return (EXIT_SUCCESS);
	return (read_file(data + ntohl(fat->offset)));
}

int					fat_32(void *data)
{
	struct fat_header	*test;
	uint32_t			i;

	test = data;
	// printf("%x -> %x (%zd)\n", *(uint32_t *)data, *(uint32_t *)(data + sizeof(struct fat_header)), sizeof(struct fat_header));
	// printf("offset = %u archs\n", ntohl(test->nfat_arch));
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
	// printf("%x -> %x (%zd)\n", *(uint32_t *)data, *(uint32_t *)(data + sizeof(struct fat_header)), sizeof(struct fat_header));
	// printf("offset = %zd\n", ((struct fat_arch *)data + sizeof(struct fat_header))->offset);
	return (read_file(data + sizeof(struct fat_header)));
}
