/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:35:43 by asyed             #+#    #+#             */
/*   Updated: 2018/04/28 16:57:42 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

int					fat_64(void *data)
{
	struct fat_header	*test;
	uint32_t			i;

	test = data;
	i = 0;
	while (htonl(i) < test->nfat_arch)
	{
		parse_fat(data, data + sizeof(struct fat_header) + (i * sizeof(struct fat_arch_64)));
		i++;
	}
	return (EXIT_SUCCESS);
}

int					fat_64_swap(void *data)
{
	// printf("%x -> %x (%zd)\n", *(uint32_t *)data, *(uint32_t *)(data + sizeof(struct fat_header)), sizeof(struct fat_header));
	// printf("offset = %zd\n", ((struct fat_arch *)data + sizeof(struct fat_header))->offset);
	return (read_file(data + sizeof(struct fat_header)));
}
