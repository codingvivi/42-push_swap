/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:12:36 by lrain             #+#    #+#             */
/*   Updated: 2026/03/30 21:58:19 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

static void	swap(t_stack s)
{
	const int	buf = s.data[s.head];

	if (s.size < 2)
		return ;
	s.data[s.head] = s.data[(s.head - 1) % s.cap];
	s.data[(s.head - 1) % s.cap] = buf;
}

void	sa(t_stack stks[2])
{
	swap(stks[e_a]);
}

void	sb(t_stack stks[2])
{
	swap(stks[e_b]);
}

void	ss(t_stack stks[2])
{
	sa(stks);
	sb(stks);
}
