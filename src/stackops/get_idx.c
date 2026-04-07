/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_idx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:25:24 by lrain             #+#    #+#             */
/*   Updated: 2026/03/31 19:55:20 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"
#include <stddef.h>
#include <sys/types.h>

/*
+ cap --> protect from negative idx/underflow
+ motion --> move accordingly
% cap --> remove protection & wrap around
*/

ssize_t	get_idx(const size_t origin, const int motion, const size_t cap)
{
	return ((ssize_t)(((origin + cap) + motion) % cap));
}

ssize_t	from_head(const t_stack s, const int motion)
{
	return (get_idx(s.head, motion, s.cap));
}
