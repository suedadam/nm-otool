/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm__.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:40:39 by asyed             #+#    #+#             */
/*   Updated: 2018/04/27 17:32:09 by asyed            ###   ########.fr       */
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
** utils
*/

char	ref_char(char *seg, char *sect);
char	grab_typec(uint8_t type, uint8_t nsect);

#endif