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

/*
+ cap --> protect from negative idx/underflow
+ motion --> move accordingly
% cap --> remove protection & wrap around
*/

size_t	get_idx(const size_t origin, const int motion, const size_t cap)
{
	return (((origin + cap) + motion) % cap);
}

size_t	i_head_plus(const t_stack s, const int motion)
{
	return (get_idx(s.head, motion, s.cap));
}
