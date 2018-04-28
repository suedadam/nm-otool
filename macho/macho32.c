/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:46:53 by asyed             #+#    #+#             */
/*   Updated: 2018/04/27 18:34:12 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

static int			dump_section(void *data, void *offset, void *upper, uint8_t *pos)
{
	struct section		*sect;
	int					i;

	sect = offset;
	while ((void *)sect < (void *)upper && i < MAX_SECT)
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
			ft_enpqueue(queue, &sym, sizeof(t_symsort), (int (*)(void *, void *))&sym_sort);
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
	int						i;
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
		if (cmd->cmd == LC_SEGMENT)
			dump_section(data, (void *)cmd + sizeof(struct segment_command), (void *)cmd + seg->cmdsize, &pos);
		else if (cmd->cmd == LC_SYMTAB)
			dump_symbols(data, (void *)cmd, queue);
		else if (cmd->cmd == LC_DYSYMTAB)
			printf("Dynamic symtable\n");
		offset += cmd->cmdsize;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	mach_32(void *data)
{
	struct mach_header	*header;

	header = (struct mach_header *)data;
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
	return (dump_commands(data, sizeof(struct mach_header), header->ncmds));
}

int	mach_32_swap(void *data)
{
	printf("wow 32 bit swapped\n");
	return (EXIT_SUCCESS);
}