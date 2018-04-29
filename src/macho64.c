/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:52:47 by asyed             #+#    #+#             */
/*   Updated: 2018/04/29 15:57:44 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

#ifdef OTOOL

static int	print_section(void *data, struct section_64 *sect)
{
	uint64_t	i;
	uint8_t		j;

	if (!(i = sect->offset))
		return (EXIT_SUCCESS);
	ft_printf("Contents of (%s,%s) section\n", sect->segname, sect->sectname);
	while (i < (sect->offset + sect->size))
	{
		j = 0;
		ft_printf("%016llx	", sect->addr + (i - sect->offset));
		while ((j + i) < (sect->offset + sect->size) && j < 16)
		{
			ft_printf("%02x ", *(unsigned char *)(data + i + j));
			j++;
		}
		ft_printf("\n");
		i += 16;
	}
	return (EXIT_SUCCESS);
}

static int	dump_section_64(void *data, void *offset, void *upper, uint8_t *pos)
{
	struct section_64	*sect;

	sect = offset;
	while ((void *)sect < (void *)upper && *pos < MAX_SECT)
	{
		if (!sect->size)
			break ;
		if (!ft_strcmp(sect->segname, "__TEXT") &&
			!ft_strcmp(sect->sectname, "__text"))
			return (print_section(data, sect));
		sect = ((void *)sect + sizeof(struct section_64));
	}
	return (EXIT_SUCCESS);
}

static int	dump_commands_64(void *data, size_t offset, uint32_t ncmds)
{
	struct load_command			*cmd;
	struct segment_command_64	*seg;
	uint32_t					i;
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
			dump_section_64(data,
				(void *)cmd + sizeof(struct segment_command_64),
				(void *)cmd + seg->cmdsize, &pos);
		offset += cmd->cmdsize;
		i++;
	}
	return (EXIT_SUCCESS);
}

#else

static int	dump_section_64(__attribute__((unused))void *data, void *offset, void *upper, uint8_t *pos)
{
	struct section_64	*sect;

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

static int	dump_symbols_64(void *data,
			struct symtab_command *symtable, t_pqueue *queue)
{
	struct nlist_64	*element;
	uint32_t		i;
	t_symsort		sym;

	i = 0;
	element = data + symtable->symoff;
	while (i < symtable->nsyms)
	{
		if (!(element->n_type & N_STAB))
		{
			sym.addr = element->n_value;
			sym.typechar = grab_typec(element->n_type, element->n_sect,
							element->n_value);
			sym.name = data + symtable->stroff + element->n_un.n_strx;
			ft_enpqueue(queue, &sym,
				sizeof(t_symsort),
				(int (*)(void *, void *))sym_sort);
		}
		element++;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	dump_commands_64(void *data, size_t offset, uint32_t ncmds)
{
	struct load_command			*cmd;
	struct segment_command_64	*seg;
	uint32_t					i;
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
			dump_section_64(data,
				(void *)cmd + sizeof(struct segment_command_64),
				(void *)cmd + seg->cmdsize, &pos);
		else if (cmd->cmd == LC_SYMTAB)
			dump_symbols_64(data, (void *)cmd, queue);
		offset += cmd->cmdsize;
		i++;
	}
	return (print_symbols(queue));
}

#endif

int			mach_64(void *data)
{
	struct mach_header_64	*header;

	header = (struct mach_header_64 *)data;
	return (dump_commands_64(data,
			sizeof(struct mach_header_64), header->ncmds));
}
