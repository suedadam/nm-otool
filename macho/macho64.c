/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:52:47 by asyed             #+#    #+#             */
/*   Updated: 2018/04/07 20:06:56 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#define EMPTYSPACES "                 "
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

struct _cpu_type_names {
  cpu_type_t cputype;
  const char *cpu_name;
};

static struct _cpu_type_names cpu_type_names[] = {
  { CPU_TYPE_I386, "i386" },
  { CPU_TYPE_X86_64, "x86_64" },
  { CPU_TYPE_ARM, "arm" },
  { CPU_TYPE_ARM64, "arm64" }
};

static const char	*cpu_type_name(cpu_type_t cpu_type)
{
	static int	cpu_type_names_size = sizeof(cpu_type_names) /
				sizeof(struct _cpu_type_names);
	int			i;

	i = 0;
	while (i < cpu_type_names_size)
	{
		if (cpu_type == cpu_type_names[i].cputype)
			return (cpu_type_names[i].cpu_name);
		i++;
	}
	return "unknown";
}

static int			dump_section_64(void *data, void *offset, void *upper)
{
	struct section_64	*sect;

	sect = offset;
	while ((void *)sect < (void *)upper)
	{
		if (!sect->size)
		{
			printf("----> section was 0 \n");
			break ;
		}
		printf("----> segment = %s,%s size = %llu (%u %u)\n", sect->segname, sect->sectname, sect->size, sect->align, sect->offset);
		printf("%x\n", *(unsigned char *)(data + sect->offset));
		printf("%x\n", *(unsigned char *)(data + sect->offset + 1));
		sect = ((void *)sect + sizeof(struct section_64));
	}
	return (EXIT_SUCCESS);
}

static void			*to_array(t_queue *queue, size_t elements)
{
	char	**array;
	int		i;
	char	*string;

	if (!(array = ft_memalloc(sizeof(char *) * (elements + 1))))
		return (NULL);
	i = 0;
	while ((string = ft_dequeue(queue)))
	{
		array[i] = string;
		i++;
	}
	free(queue);
	return (array);
}

static void			*conv_strtable(void *table, size_t size)
{
	char	*tmp;
	t_queue	*queue;
	size_t	len;
	size_t	elements;

	if (!(queue = new_queue()))
		return (NULL);
	elements = 0;
	while (size > 0)
	{
		if (!(tmp = ft_strdup(table)))
		{
			printf("Empty entry?\n");
			break ;
		}
		printf("tmp = %s\n", tmp);
		len = ft_strlen(tmp);
		if (ft_enqueue(queue, tmp, len) == EXIT_FAILURE)
		{
			printf("Failed to insert into queue?\n");
			return (NULL);
		}
		free(tmp);
		table += len + 1;
		size -= len + 1;
		elements++;
	}
	return (to_array(queue, elements)); //Change to return recalculated array.
}

static char 		grab_typec(uint8_t type, uint8_t nsect)
{
	uint8_t	ntype;

	ntype = type & N_TYPE;
	if (ntype == N_UNDF)
		return ('U');
	else if (ntype == N_ABS)
		return ('A');
	else if (ntype == N_SECT)
	{
		if (nsect & NO_SECT)
			return ('t');
		else
			return ('T');
	}
	else if (ntype == N_PBUD)
		return ('P');
	else if (ntype == N_INDR)
		return ('I');
	else
		return ('?');
}

static int 			dump_symbols_64(void *data, struct symtab_command *symtable)
{
	char			**strtable = NULL;
	struct nlist_64	*element;
	uint32_t		i;
	uint8_t			type;

	if (!(strtable = conv_strtable(data + symtable->stroff, symtable->strsize)))
		return (EXIT_FAILURE);
	i = 0;
	element = data + symtable->symoff;
	while (i < symtable->nsyms)
	{
		(element->n_value) ? printf("%016llx ", element->n_value) : printf(EMPTYSPACES);
		printf("%c ", grab_typec(element->n_type, element->n_sect));
		printf("%s\n", data + symtable->stroff + element->n_un.n_strx);
		element++;
		i++;
	}
}

static int 			dump_commands_64(void *data, size_t offset, uint32_t ncmds)
{
	struct load_command	*cmd;
	struct segment_command_64 *seg;
	int	i;

	i = 0;
	while (i < ncmds)
	{
		cmd = (struct load_command	*)(data + offset);
		seg = (struct segment_command_64 *)(data + offset);
		if (cmd->cmd == LC_SEGMENT_64)
		{
			printf("segname: \"%s\" (addr = %p) (%d)\n", seg->segname, seg->fileoff, seg->cmdsize);
			dump_section_64(data, (void *)cmd + sizeof(struct segment_command_64), (void *)cmd + seg->cmdsize);
			// exit(EXIT_FAILURE);	
		}
		else if (cmd->cmd == LC_SYMTAB)
		{
			printf("Symbol table!!! %d\n", cmd->cmdsize);
			dump_symbols_64(data, (void *)cmd);
		}
		offset += cmd->cmdsize;
		i++;
	}
	return (EXIT_SUCCESS);	
}

int					mach_64(void *data)
{
	struct mach_header_64	*header;

	header = (struct mach_header_64 *)data;
	printf("%s\n", cpu_type_name(header->cputype));
	return (dump_commands_64(data, sizeof(struct mach_header_64), header->ncmds));
}