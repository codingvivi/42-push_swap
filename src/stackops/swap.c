/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:12:36 by lrain             #+#    #+#             */
/*   Updated: 2026/03/31 19:53:40 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "libft.h"
#include "stacks.h"

static void	swap(t_stack *s)
{
	const int	buf = s->data[s->head];

	if (s->size < 2)
		return ;
	s->data[s->head] = s->data[from_head(*s, -1)];
	s->data[from_head(*s, -1)] = buf;
}

void	sa(t_stack *stks[2])
{
	swap(stks[e_a]);
	ft_printf("sa\n");
}

void	sb(t_stack *stks[2])
{
	swap(stks[e_b]);
	ft_printf("sb\n");
}

void	ss(t_stack *stks[2])
{
	swap(stks[e_a]);
	swap(stks[e_b]);
	ft_printf("ss\n");
}
