/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 01:55:18 by asyed             #+#    #+#             */
/*   Updated: 2018/04/29 16:38:44 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# include <stdint.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <mach/mach_types.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <mach/mach_types.h>
# include "libft.h"

typedef struct	s_headertype
{
	uint32_t	magic;
	int			(*f)(void *data);
}				t_headertype;

int				read_file(void *data);
int				mach_32(void *data);
int				mach_32_swap(void *data);
int				mach_64(void *data);
int				mach_64_swap(void *data);
int				fat_32(void *data);
int				fat_32_swap(void *data);
int				fat_64(void *data);
int				fat_64_swap(void *data);
int				archivelib_64(void *data);

char			g_sectnames[MAX_SECT + 1];

#endif
