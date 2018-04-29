/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 13:07:01 by asyed             #+#    #+#             */
/*   Updated: 2018/04/28 20:43:26 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

// void	*malloc(size_t size)
// {
// 	void	*ret;
// 	t_meta	*new_h;

// 	if (!(ret = malloc(size + sizeof(t_meta))))
// 		return (NULL);
// 	ft_bzero(ret, size + sizeof(t_meta));
// 	new_h = ret;
// 	new_h->len = size;
// 	return (ret + sizeof(t_meta));
// }

// void	*meta_realloc(void *old, size_t newsize)
// {
// 	void		*new;
// 	t_meta		*old_h;
// 	t_meta		*new_h;

// 	if (!old)
// 		return (malloc(newsize));
// 	old_h = old - sizeof(t_meta);
// 	if (old_h->len >= newsize)
// 		return (old);
// 	if (!(new = malloc(newsize)))
// 		return (NULL);
// 	new_h = new - sizeof(t_meta);
// 	memcpy(new, old, old_h->len);
// 	free(old_h);
// 	return (new);
// }

// void	free(void *old)
// {
// 	if (!old)
// 		return ;
// 	free(old - sizeof(t_meta));
// }
