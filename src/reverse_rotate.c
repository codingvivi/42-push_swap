/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:43:11 by lrain             #+#    #+#             */
/*   Updated: 2026/03/30 22:43:53 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	reverse_rotate(t_stack s)
{
	s.head = (s.head + 1) % s.size;
}

void	rra(t_stack stks[2])
{
	reverse_rotate(stks[e_a]);
}

void	rrb(t_stack stks[2])
{
	reverse_rotate(stks[e_b]);
}
