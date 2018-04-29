/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach32_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:46:53 by asyed             #+#    #+#             */
/*   Updated: 2018/04/29 16:22:11 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

#ifdef OTOOL

static int	print_section(void *data, struct section *sect)
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

static int	dump_section(void *data, void *offset, void *upper, uint8_t *pos)
{
	struct section		*sect;

	sect = offset;
	while ((void *)sect < (void *)upper && *pos < MAX_SECT)
	{
		if (!sect->size)
			break ;
		if (!ft_strcmp(sect->segname, "__TEXT") &&
			!ft_strcmp(sect->sectname, "__text"))
			return (print_section(data, sect));
		sect = ((void *)sect + sizeof(struct section));
		(*pos)++;
	}
	return (EXIT_SUCCESS);
}

static int	dump_commands(void *data, size_t offset, uint32_t ncmds)
{
	struct load_command		*cmd;
	struct segment_command	*seg;
	uint32_t				i;
	uint8_t					pos;

	i = 0;
	pos = 1;
	while (i < ncmds)
	{
		cmd = (struct load_command *)(data + offset);
		seg = (struct segment_command *)(data + offset);
		if (cmd->cmd == htonl(LC_SEGMENT))
			dump_section(data,
				(void *)cmd + sizeof(struct segment_command),
				(void *)cmd + ntohl(seg->cmdsize), &pos);
		offset += ntohl(cmd->cmdsize);
		i++;
	}
	return (EXIT_SUCCESS);
}

#else

static int	dump_section(void *offset, void *upper, uint8_t *pos)
{
	struct section		*sect;

	sect = offset;
	while ((void *)sect < (void *)upper && *pos < MAX_SECT)
	{
		if (!sect->size)
			break ;
		g_sectnames[*pos] = ref_char(sect->sectname);
		sect = ((void *)sect + sizeof(struct section));
		(*pos)++;
	}
	return (EXIT_SUCCESS);
}

static int	dump_symbols(void *data,
			struct symtab_command *symtable, t_pqueue *queue)
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
			sym.typechar = grab_typec(element->n_type,
							element->n_sect, (uint64_t)ntohl(element->n_value));
			sym.name = data + ntohl(symtable->stroff) +
						ntohl(element->n_un.n_strx);
			ft_enpqueue(queue, &sym,
					sizeof(t_symsort),
					(int (*)(void *, void *))sym_sort);
		}
		element++;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	dump_commands(void *data, size_t offset, uint32_t ncmds)
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
			dump_section((void *)cmd + sizeof(struct segment_command),
				(void *)cmd + ntohl(seg->cmdsize), &pos);
		else if (cmd->cmd == htonl(LC_SYMTAB))
			dump_symbols(data, (void *)cmd, queue);
		offset += ntohl(cmd->cmdsize);
		i++;
	}
	return (print_symbols(queue));
}

#endif

int			mach_32_swap(void *data)
{
	struct mach_header	*header;

	header = (struct mach_header *)data;
	return (dump_commands(data,
		sizeof(struct mach_header),
		htonl(header->ncmds)));
}
