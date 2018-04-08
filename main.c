/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 01:48:32 by asyed             #+#    #+#             */
/*   Updated: 2018/04/07 19:49:03 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
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
#include <mach/mach_types.h>

t_headertype  headers[] = {
  {MH_MAGIC, mach_32},
  // {MH_CIGAM, mach_32_swap},
  {MH_MAGIC_64, mach_64},
  // {MH_CIGAM_64, mach_64_swap},
  // {FAT_MAGIC, fat_32},
  // {FAT_CIGAM, fat_32_swap},
  // {FAT_MAGIC_64, fat_64},
  // {FAT_CIGAM_64, fat_64_swap},
  {0, NULL},
};

static int read_file(void *data)
{
	uint32_t	magic;
	int			i;

	magic = *(uint32_t *)data;
	i = 0;
	while (headers[i].magic)
	{
		if (headers[i].magic == magic)
			return ((*headers[i].f)(data));
		i++;
	}
	printf("Unsupported mode %x\n", magic);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	int			fd;
	struct stat	st_buf;
	void		*data;

	if (argc < 2)
		return (EXIT_SUCCESS);
	if ((fd = open(argv[1], O_RDONLY)) == -1
		|| fstat(fd, &st_buf) == -1
		|| (data = mmap(NULL, st_buf.st_size, PROT_READ, MAP_SHARED | MAP_FILE, fd, 0)) == (void *)-1)
		return (EXIT_FAILURE);
	if (read_file(data) == EXIT_FAILURE)
		printf("Error \"%s\"\n", strerror(errno));
	close(fd);
	munmap(data, st_buf.st_size);
	return (EXIT_SUCCESS);
}

// int			main(int argc, char *argv[])
// {
// 	unsigned char		*data;
// 	int					fd;
// 	int					i;
// 	struct stat			st_buf;
// 	struct mach_header	*metadata;
// 	struct load_command	*cmd;

// 	if ((fd = open(argv[1], O_RDONLY)) == -1)
// 	{
// 		printf("Open: Error: %s\n", strerror(errno));
// 		return (-1);
// 	}
// 	if (fstat(fd, &st_buf) == -1)
// 	{
// 		printf("FD: Error: %s\n", strerror(errno));
// 		return (-1);
// 	}
// 	if ((data = mmap(NULL, st_buf.st_size, PROT_READ, MAP_SHARED | MAP_FILE, fd, 0)) == (void *)-1)
// 	{
// 		printf("mmap: Error: %s\n", strerror(errno));
// 		return (-1);
// 	}
// 	metadata = (struct mach_header *)data;
// 	data += sizeof(struct mach_header_64);
// 	i = 0;
// 	while (i < metadata->ncmds)
// 	{
// 		cmd = (struct load_command *)data;
// 		if (cmd->cmd == LC_SYMTAB)
// 		{
// 			dump_table((struct symtab_command *)cmd, (unsigned char *)metadata);
// 			break ;
// 		}
// 		i++;
// 		data += cmd->cmdsize;
// 	}
// }