/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_into_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/11 01:23:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pickop.h"
#include "push.h"
#include "stacks.h"
#include "value_fetchers.h"
#include <stddef.h>
#include <sys/types.h>

static ssize_t		combined_cost(ssize_t topb_c, ssize_t desta_c);
static t_idx_cost	cheapest_idx(ssize_t **mc, size_t size_b);
static void			init_ops(t_op ops[3], ssize_t mags[3],
						const ssize_t rots[2]);

void	sort_into_a(ssize_t **mc, t_stack *stks[2])
{
	const t_idx_cost	cheapest = cheapest_idx(mc, stks[e_b]->size);
	ssize_t				rotations[2];
	t_op				ops[3];
	ssize_t				magnitudes[3];
	ssize_t				i;

	rotations[e_a] = mc[e_desta][cheapest.idx];
	rotations[e_b] = mc[e_topb][cheapest.idx];
	init_ops(ops, magnitudes, rotations);
	i = e_both;
	while (i >= e_a)
	{
		while (magnitudes[i]-- > 0)
			ops[i](stks);
		i--;
	}
	pa(stks);
}

static ssize_t	combined_cost(ssize_t topb_c, ssize_t desta_c)
{
	if (topb_c > 0)
	{
		if (desta_c >= 0)
			return (max(topb_c, desta_c));
		return (topb_c + ps_abs(desta_c));
	}
	if (desta_c >= 0)
		return (ps_abs(topb_c) + desta_c);
	return (ps_abs(min(topb_c, desta_c)));
}

static t_idx_cost	cheapest_idx(ssize_t **mc, size_t size_b)
{
	t_idx_cost	curr;
	t_idx_cost	minc;

	curr.idx = 0;
	while (curr.idx < size_b)
	{
		curr.cost = combined_cost(mc[e_topb][curr.idx], mc[e_desta][curr.idx]);
		if (curr.idx == 0 || curr.cost < minc.cost)
			minc = curr;
		curr.idx++;
	}
	return (minc);
}

static void	init_ops(t_op ops[3], ssize_t mags[3], const ssize_t rots[2])
{
	ops[e_a] = pick_a(rots[e_a]);
	ops[e_b] = pick_b(rots[e_b]);
	ops[e_both] = NULL;
	mags[e_a] = ps_abs(rots[e_a]);
	mags[e_b] = ps_abs(rots[e_b]);
	mags[e_both] = 0;
	if ((rots[e_b] < 0) == (rots[e_a] < 0) && rots[e_b] && rots[e_a])
	{
		ops[e_both] = pick_both(rots[e_b]);
		mags[e_both] = min(mags[e_a], mags[e_b]);
		mags[e_a] -= mags[e_both];
		mags[e_b] -= mags[e_both];
	}
}
