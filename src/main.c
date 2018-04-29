/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 01:48:32 by asyed             #+#    #+#             */
/*   Updated: 2018/04/29 16:55:38 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_int.h"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mach/mach_types.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <mach/mach_types.h>

t_headertype	g_headers[] = {
	{MH_MAGIC, mach_32},
	{MH_CIGAM, mach_32_swap},
	{MH_MAGIC_64, mach_64},
	{MH_CIGAM_64, mach_64_swap},
	{FAT_MAGIC, fat_32},
	{FAT_CIGAM, fat_32},
	{FAT_MAGIC_64, fat_64},
	{FAT_CIGAM_64, fat_64_swap},
	{0, NULL},
};

int	read_file(void *data)
{
	uint32_t	magic;
	int			i;

	magic = *(uint32_t *)data;
	i = 0;
	while (g_headers[i].magic)
	{
		if (g_headers[i].magic == magic)
			return ((*g_headers[i].f)(data));
		i++;
	}
	ft_printf("Unsupported file magic %x\n", magic);
	return (EXIT_FAILURE);
}

int	parse_files(int argc, char *argv[])
{
	int			fd;
	int8_t		ret;
	struct stat	st_buf;
	void		*data;
	int			i;

	i = 1;
	while (i < argc)
	{
		if (!argv[i])
			i++;
		ft_printf("\n%s:\n", argv[i]);
		if ((fd = open(argv[i], O_RDONLY)) == -1
			|| fstat(fd, &st_buf) == -1
			|| (data = mmap(NULL, st_buf.st_size, PROT_READ,
				MAP_SHARED | MAP_FILE, fd, 0)) == (void *)-1
			|| (ret = read_file(data)) == EXIT_FAILURE)
			ft_printf("Error: \"%s\"\n", ft_strerror(errno));
		close(fd);
		munmap(data, st_buf.st_size);
		i++;
	}
	return (ret);
}

int	main(int argc, char *argv[])
{
	int	ret;

	if (argc < 2)
		return (EXIT_SUCCESS);
	if ((ret = parse_flags(argc, argv)) == EXIT_FAILURE)
	{
		ft_printf("Error: \"%s\"\n", ft_strerror(errno));
		return (ret);
	}
	return (parse_files(argc, argv));
}
