/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:48:14 by asyed             #+#    #+#             */
/*   Updated: 2018/04/29 16:46:16 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_int.h"

int	parse_flags(int argc, char *argv[])
{
	int		i;
	int8_t	ret;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && ft_strlen(argv[i]) == 2)
		{
			ret = pick_sort(argv[i][1]);
			argv[i] = NULL;
			return (ret);
		}
		i++;
	}
	return (pick_sort('0'));
}
