/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archivelib_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:09:15 by asyed             #+#    #+#             */
/*   Updated: 2018/04/28 19:47:36 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"
#include <stdio.h>
#include <unistd.h>
#include <mach-o/ranlib.h>

int					archivelib_64(void *data)
{
	struct ranlib_64 *lib;

	lib = (void *)(data + sizeof(uint64_t));
	// if (*(uint32_t *)data == 0x72613c21)
		// printf("Yeah I'm correct there...?\n");
	// printf("%llx\n", lib->ran_un.ran_strx);
	// printf("Lib name - %llu\n", lib->ran_un.ran_strx);
	// printf("Yesss!\n");
	return (EXIT_SUCCESS);
}