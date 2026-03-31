/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:43:11 by lrain             #+#    #+#             */
/*   Updated: 2026/03/31 20:41:23 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "stacks.h"

void	reverse_rotate(t_stack *s)
{
	s->head = from_head(*s, +1);
	s->data[s->head] = s->data[from_head(*s, -s->size)];
}

void	rra(t_stack stks[2])
{
	reverse_rotate(&stks[e_a]);
}

void	rrb(t_stack stks[2])
{
	reverse_rotate(&stks[e_b]);
}

void	rrr(t_stack stks[2])
{
	rra(stks);
	rrb(stks);
}
