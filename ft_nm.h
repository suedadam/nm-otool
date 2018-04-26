/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 01:55:18 by asyed             #+#    #+#             */
/*   Updated: 2018/04/07 19:56:36 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <mach/mach_types.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach/mach_types.h>
#include "libft.h"

typedef struct  s_headertype
{
  uint32_t  magic;
  int     (*f)(void *data);
}       t_headertype;

int		mach_32(void *data);
int		mach_64(void *data);

// typedef int	cpu_type_t;
// typedef int	cpu_subtype_t;
// typedef int		vm_prot_t;

// struct mach_header {
//   uint32_t      magic;
//   cpu_type_t    cputype;
//   cpu_subtype_t cpusubtype;
//   uint32_t      filetype;
//   uint32_t      ncmds;
//   uint32_t      sizeofcmds;
//   uint32_t      flags;
// };

// struct segment_command {
//   uint32_t  cmd;
//   uint32_t  cmdsize;
//   char      segname[16];
//   uint32_t  vmaddr;
//   uint32_t  vmsize;
//   uint32_t  fileoff;
//   uint32_t  filesize;
//   vm_prot_t maxprot;
//   vm_prot_t initprot;
//   uint32_t  nsects;
//   uint32_t  flags;
// };

#endif