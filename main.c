/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 01:48:32 by asyed             #+#    #+#             */
/*   Updated: 2018/03/21 03:15:53 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <mach/mach_types.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach/mach_types.h>

static void	dump_table(struct symtab_command *symtab, unsigned char *data)
{
	struct nlist_64	*nlist;
	int				i;
	char			type;
	unsigned char	*name;

	nlist = (struct nlist_64 *)(data + symtab->symoff);
	i = 0;
	while (i < symtab->nsyms)
	{
		name = data + symtab->stroff + nlist->n_un.n_strx;
		if ((nlist->n_type & N_TYPE) == N_UNDF)
			printf("                 U");
		if ((nlist->n_type & N_TYPE) == N_SECT)
			printf("%016llx T", nlist->n_value);
		printf(" %s\n", name);
		i++;
		nlist++;
	}
}

int			main(int argc, char *argv[])
{
	unsigned char		*data;
	int					fd;
	int					i;
	struct stat			st_buf;
	struct mach_header	*metadata;
	struct load_command	*cmd;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		printf("Open: Error: %s\n", strerror(errno));
		return (-1);
	}
	if (fstat(fd, &st_buf) == -1)
	{
		printf("FD: Error: %s\n", strerror(errno));
		return (-1);
	}
	if ((data = mmap(NULL, st_buf.st_size, PROT_READ, MAP_SHARED | MAP_FILE, fd, 0)) == (void *)-1)
	{
		printf("mmap: Error: %s\n", strerror(errno));
		return (-1);
	}
	metadata = (struct mach_header *)data;
	data += sizeof(struct mach_header_64);
	i = 0;
	while (i < metadata->ncmds)
	{
		cmd = (struct load_command *)data;
		if (cmd->cmd == LC_SYMTAB)
		{
			dump_table((struct symtab_command *)cmd, (unsigned char *)metadata);
			break ;
		}
		i++;
		data += cmd->cmdsize;
	}
}