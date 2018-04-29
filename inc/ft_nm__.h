/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm__.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:40:39 by asyed             #+#    #+#             */
/*   Updated: 2018/04/28 20:29:40 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM____H
# define FT_NM____H
# include "libft.h"
# include "ft_nm.h"
# define EMPTYSPACES "                 "

typedef struct	s_symsort
{
	uint64_t	addr;
	char		typechar;
	char		*name;	
}				t_symsort;

/*
** fat
*/
int		parse_fat(void *data, struct fat_arch *fat);

/*
** utils
*/

char	ref_char(char *seg, char *sect);
char	grab_typec(uint8_t type, uint8_t nsect, uint64_t value);
int		(*sym_sort)(t_symsort *old, t_symsort *new);
int 	print_symbols(t_pqueue *queue);

/*
** sort
*/
int		pick_sort(char c);

/*
** flags
*/

int		parse_flags(int argc, char *argv[]);

#endif