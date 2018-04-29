/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:48:14 by asyed             #+#    #+#             */
/*   Updated: 2018/04/27 18:51:03 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm__.h"

int	parse_flags(int argc, char *argv[])
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && ft_strlen(argv[i]) == 2)
			return (pick_sort(argv[i][1]));
		i++;
	}
	return (pick_sort('0'));
}
