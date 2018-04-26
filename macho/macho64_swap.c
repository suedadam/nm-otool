/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:52:47 by asyed             #+#    #+#             */
/*   Updated: 2018/04/26 15:44:52 by asyed            ###   ########.fr       */
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

static int			dump_section_64(void *data, void *offset, void *upper, uint8_t *pos)
{
	struct section_64	*sect;
	int					i;

	sect = offset;
	while ((void *)sect < (void *)upper && i < MAX_SECT)
	{
		if (!sect->size)
			break ;
		g_sectnames[*pos] = ref_char(sect->segname, sect->sectname);
		// printf("----> segment = %s,%s size = %llu (%u %u) %d -> %c\n", sect->segname, sect->sectname, sect->size, sect->align, sect->offset, *pos, g_sectnames[*pos]);
		// printf("%x\n", *(unsigned char *)(data + sect->offset));
		// printf("%x\n", *(unsigned char *)(data + sect->offset + 1));
		sect = ((void *)sect + sizeof(struct section_64));
		(*pos)++;
	}
	return (EXIT_SUCCESS);
}

static int 			dump_symbols_64(void *data, struct symtab_command *symtable)
{
	struct nlist_64	*element;
	uint32_t		i;
	uint8_t			type;

	i = 0;
	element = data + symtable->symoff;
	while (i < symtable->nsyms)
	{
		if (!(element->n_type & N_STAB))
		{
			(element->n_value) ? printf("%016llx ", element->n_value) : printf(EMPTYSPACES);
			printf("%c ", grab_typec(element->n_type, element->n_sect));
			printf("%s\n", data + symtable->stroff + element->n_un.n_strx);
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

	i = 0;
	pos = 1;
	while (i < ncmds)
	{ 
		cmd = (struct load_command	*)(data + offset);
		seg = (struct segment_command_64 *)(data + offset);
		if (cmd->cmd == LC_SEGMENT_64)
			dump_section_64(data, (void *)cmd + sizeof(struct segment_command_64), (void *)cmd + seg->cmdsize, &pos);
		else if (cmd->cmd == LC_SYMTAB)
			dump_symbols_64(data, (void *)cmd);
		else if (cmd->cmd == LC_DYSYMTAB)
			printf("Dynamic symtable\n");
		offset += cmd->cmdsize;
		i++;
	}
	return (EXIT_SUCCESS);	
}

int					mach_64_swap(void *data)
{
	// struct mach_header_64	*header;

	printf("Its a swapped one!\n");
	return (EXIT_SUCCESS);
	// header = (struct mach_header_64 *)data;
	// printf("%s\n", cpu_type_name(header->cputype));
	// if (header->filetype == MH_OBJECT)
	// 	printf("Object file!\n");
	// else if (header->filetype == MH_EXECUTE)
	// 	printf("Executable\n");
	// else if (header->filetype == MH_EXECUTE)
	// 	printf("Bundle/Plugin\n");
	// else if (header->filetype == MH_DYLIB)
	// 	printf("Dynamic library\n");
	// else if (header->filetype == MH_PRELOAD)
	// 	printf("Preloading patch?\n");
	// else if (header->filetype == MH_CORE)
	// 	printf("Core files - a/k/a crash files\n");
	// else if (header->filetype == MH_DYLINKER)
	// 	printf("Dynamic linker library file\n");
	// else if (header->filetype == MH_DSYM)
	// 	printf("symbol information for file\n");
	// return (dump_commands_64(data, sizeof(struct mach_header_64), header->ncmds));
}
