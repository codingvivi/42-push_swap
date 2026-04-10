/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_into_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 20:00:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pickop.h"
#include "push.h"
#include "stacks.h"
#include "value_fetchers.h"
#include <sys/types.h>

static t_idx_cost	cheapest_idx(ssize_t **mc, size_t size_b)
{
	t_idx_cost	curr;
	t_idx_cost	minc;
	ssize_t		topb_c;
	ssize_t		desta_c;

	curr.idx = 0;
	while (curr.idx < size_b)
	{
		topb_c = mc[e_topb][curr.idx];
		desta_c = mc[e_desta][curr.idx];
		if (topb_c > 0)
		{
			if (desta_c >= 0)
				curr.cost = max(topb_c, desta_c);
			else
				curr.cost = topb_c + ps_abs(desta_c);
		}
		else
		{
			if (desta_c >= 0)
				curr.cost = ps_abs(topb_c) + desta_c;
			else
				curr.cost = ps_abs(min(topb_c, desta_c));
		}
		if (curr.idx == 0 || curr.cost < minc.cost)
			minc = curr;
		curr.idx++;
	}
	return (minc);
}

static void	init_ops(t_op ops[3], ssize_t mags[3], const ssize_t n[2])
{
	ops[e_a] = pick_a(n[e_a]);
	ops[e_b] = pick_b(n[e_b]);
	ops[e_both] = NULL;
	mags[e_a] = ps_abs(n[e_a]);
	mags[e_b] = ps_abs(n[e_b]);
	mags[e_both] = 0;
	if ((n[e_b] < 0) == (n[e_a] < 0) && n[e_b] && n[e_a])
	{
		ops[e_both] = pick_both(n[e_b]);
		mags[e_both] = min(mags[e_a], mags[e_b]);
		mags[e_a] -= mags[e_both];
		mags[e_b] -= mags[e_both];
	}
}

void	sort_into_a(ssize_t **mc, t_stack *stks[2])
{
	const t_idx_cost	c = cheapest_idx(mc, stks[e_b]->size);
	const ssize_t		n[2] = {mc[e_desta][c.idx], mc[e_topb][c.idx]};
	t_op				ops[3];
	ssize_t				mags[3];
	ssize_t				i;

	init_ops(ops, mags, n);
	i = e_both;
	while (i >= e_a)
	{
		while (mags[i]-- > 0)
			ops[i](stks);
		i--;
	}
	pa(stks);
}
