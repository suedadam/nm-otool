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

static const char *cpu_type_name(cpu_type_t cpu_type) {
  static int cpu_type_names_size = sizeof(cpu_type_names) / sizeof(struct _cpu_type_names);
  for (int i = 0; i < cpu_type_names_size; i++ ) {
    if (cpu_type == cpu_type_names[i].cputype) {
      return cpu_type_names[i].cpu_name;
    }
  }

  return "unknown";
}

static int dump_commands_64(void *data, size_t offset, uint32_t ncmds)
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
			printf("segname: \"%s\"\n", seg->segname);
		offset += cmd->cmdsize;
		i++;
	}
	return (EXIT_SUCCESS);	
}

int	mach_64(void *data)
{
	struct mach_header_64	*header;
	// uint32_t				ncmds;
	// size_t					cmds_offset;

	// cmds_offset = 0;
	header = (struct mach_header_64 *)data;
	// ncmds = header->ncmds;
	// cmds_offset += sizeof(struct mach_header_64);
	printf("%s\n", cpu_type_name(header->cputype));
	return (dump_commands_64(data, sizeof(struct mach_header_64), header->ncmds));
}