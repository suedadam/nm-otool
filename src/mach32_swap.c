/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach32_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:46:53 by asyed             #+#    #+#             */
/*   Updated: 2018/04/28 19:47:48 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

static int			dump_section(__attribute__((unused)) void *data, void *offset, void *upper, uint8_t *pos)
{
	struct section		*sect;

	sect = offset;
	while ((void *)sect < (void *)upper && *pos < MAX_SECT)
	{
		if (!sect->size)
			break ;
		g_sectnames[*pos] = ref_char(sect->segname, sect->sectname);
		sect = ((void *)sect + sizeof(struct section));
		(*pos)++;
	}
	return (EXIT_SUCCESS);
}

static int 			dump_symbols(void *data, struct symtab_command *symtable, t_pqueue *queue)
{
	struct nlist	*element;
	uint32_t		i;
	t_symsort		sym;

	i = 0;
	element = data + ntohl(symtable->symoff);
	while (i < ntohl(symtable->nsyms))
	{
		if (!(element->n_type & N_STAB))
		{
			sym.addr = ntohl(element->n_value);
			sym.typechar = grab_typec(element->n_type, element->n_sect, (uint64_t)ntohl(element->n_value));
			sym.name = data + ntohl(symtable->stroff) + ntohl(element->n_un.n_strx);
			ft_enpqueue(queue, &sym, sizeof(t_symsort), (int (*)(void *, void *))sym_sort);
		}
		element++;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int 	dump_commands(void *data, size_t offset, uint32_t ncmds)
{
	struct load_command		*cmd;
	struct segment_command	*seg;
	uint32_t				i;
	uint8_t					pos;
	t_pqueue				*queue;

	i = 0;
	pos = 1;
	if (!(queue = init_pqueue()))
		return (EXIT_FAILURE);
	while (i < ncmds)
	{
		cmd = (struct load_command *)(data + offset);
		seg = (struct segment_command *)(data + offset);
		if (cmd->cmd == htonl(LC_SEGMENT))
			dump_section(data, (void *)cmd + sizeof(struct segment_command), (void *)cmd + ntohl(seg->cmdsize), &pos);
		else if (cmd->cmd == htonl(LC_SYMTAB))
			dump_symbols(data, (void *)cmd, queue);
		// else if (cmd->cmd == htonl(LC_DYSYMTAB))
			// printf("Dynamic symtable\n");
		offset += ntohl(cmd->cmdsize);
		i++;
	}
	return (print_symbols(queue));
}

int		mach_32_swap(void *data)
{
	struct mach_header	*header;

	header = (struct mach_header *)data;
	// if (header->filetype == htonl(MH_OBJECT))
	// 	printf("Object file!\n");
	// else if (header->filetype == htonl(MH_EXECUTE))
	// 	printf("Executable\n");
	// else if (header->filetype == htonl(MH_EXECUTE))
	// 	printf("Bundle/Plugin\n");
	// else if (header->filetype == htonl(MH_DYLIB))
	// 	printf("Dynamic library\n");
	// else if (header->filetype == htonl(MH_PRELOAD))
	// 	printf("Preloading patch?\n");
	// else if (header->filetype == htonl(MH_CORE))
	// 	printf("Core files - a/k/a crash files\n");
	// else if (header->filetype == htonl(MH_DYLINKER))
	// 	printf("Dynamic linker library file\n");
	// else if (header->filetype == htonl(MH_DSYM))
	// 	printf("symbol information for file\n");
	return (dump_commands(data, sizeof(struct mach_header), htonl(header->ncmds)));
}