/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:40:39 by asyed             #+#    #+#             */
/*   Updated: 2018/04/29 16:41:35 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_INT_H
# define FT_NM_INT_H
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
** utils
*/

char			ref_char(char *sect);
char			grab_typec(uint8_t type, uint8_t nsect, uint64_t value);
int				(*g_sym_sort)(t_symsort *old, t_symsort *new);
int				print_symbols(t_pqueue *queue);

/*
** sort
*/
int				pick_sort(char c);

/*
** flags
*/

int				parse_flags(int argc, char *argv[]);

#endif
