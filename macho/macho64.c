/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:52:47 by asyed             #+#    #+#             */
/*   Updated: 2018/04/27 18:44:01 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

/*
**
	struct mach_header_64 {
		uint32_t	magic;		// mach magic number identifier
		cpu_type_t	cputype;	// cpu specifier
		cpu_subtype_t	cpusubtype;	// machine specifier
		uint32_t	filetype;	// type of file
		uint32_t	ncmds;		// number of load commands
		uint32_t	sizeofcmds;	// the size of all the load commands
		uint32_t	flags;		// flags
		uint32_t	reserved;	// reserved
	};
*/

static int			dump_section_64(void *data, void *offset, void *upper, uint8_t *pos)
{
	struct section_64	*sect;
	int					i;

	sect = offset;
	while ((void *)sect < (void *)upper && *pos < MAX_SECT)
	{
		if (!sect->size)
			break ;
		g_sectnames[*pos] = ref_char(sect->segname, sect->sectname);
		sect = ((void *)sect + sizeof(struct section_64));
		(*pos)++;
	}
	return (EXIT_SUCCESS);
}

static int 			dump_symbols_64(void *data, struct symtab_command *symtable, t_pqueue *queue)
{
	struct nlist_64	*element;
	uint32_t		i;
	uint8_t			type;
	t_symsort		sym;

	i = 0;
	element = data + symtable->symoff;
	while (i < symtable->nsyms)
	{
		if (!(element->n_type & N_STAB))
		{
			sym.addr = element->n_value;
			sym.typechar = grab_typec(element->n_type, element->n_sect);
			sym.name = data + symtable->stroff + element->n_un.n_strx;
			ft_enpqueue(queue, &sym, sizeof(t_symsort), (int (*)(void *, void *))sym_sort);
		}
		element++;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int 			dump_commands_64(void *data, size_t offset, uint32_t ncmds)
{
	struct load_command			*cmd;
	struct segment_command_64	*seg;
	int							i;
	uint8_t						pos;
	t_pqueue					*queue;

	i = 0;
	pos = 1;
	if (!(queue = init_pqueue()))
		return (EXIT_FAILURE);
	while (i < ncmds)
	{ 
		cmd = (struct load_command	*)(data + offset);
		seg = (struct segment_command_64 *)(data + offset);
		if (cmd->cmd == LC_SEGMENT_64)
			dump_section_64(data, (void *)cmd + sizeof(struct segment_command_64), (void *)cmd + seg->cmdsize, &pos);
		else if (cmd->cmd == LC_SYMTAB)
			dump_symbols_64(data, (void *)cmd, queue);
		else if (cmd->cmd == LC_DYSYMTAB)
			printf("Dynamic symtable\n");
		offset += cmd->cmdsize;
		i++;
	}
	return (print_symbols(queue));
}

int					mach_64(void *data)
{
	struct mach_header_64	*header;

	header = (struct mach_header_64 *)data;
	if (header->filetype == MH_OBJECT)
		printf("Object file!\n");
	else if (header->filetype == MH_EXECUTE)
		printf("Executable\n");
	else if (header->filetype == MH_EXECUTE)
		printf("Bundle/Plugin\n");
	else if (header->filetype == MH_DYLIB)
		printf("Dynamic library\n");
	else if (header->filetype == MH_PRELOAD)
		printf("Preloading patch?\n");
	else if (header->filetype == MH_CORE)
		printf("Core files - a/k/a crash files\n");
	else if (header->filetype == MH_DYLINKER)
		printf("Dynamic linker library file\n");
	else if (header->filetype == MH_DSYM)
		printf("symbol information for file\n");
	return (dump_commands_64(data, sizeof(struct mach_header_64), header->ncmds));
}
