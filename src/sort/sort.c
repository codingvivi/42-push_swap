/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:07:54 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 01:55:51 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cost_ops.h"
#include "lis.h"
#include "print_stacks.h"
#include "push.h"
#include "reverse_rotate.h"
#include "rotate.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

static ssize_t	ps_abs(ssize_t nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}

static ssize_t	max(ssize_t x, ssize_t y)
{
	if (x < y)
		x = y;
	return (x);
}

static ssize_t	min(ssize_t x, ssize_t y)
{
	if (x > y)
		x = y;
	return (x);
}

static void	push_non_lis(t_stack stks[2], t_subseq lis)
{
	const t_stack	*a = &stks[e_a];
	const size_t	n = a->size;
	size_t			i;
	size_t			j;
	bool			is_lis;

	i = 0;
	while (i < n)
	{
		j = 0;
		is_lis = false;
		while (j < lis.size)
		{
			if (a->data[a->head] == lis.seq[j])
			{
				is_lis = true;
				break ;
			}
			j++;
		}
		if (is_lis)
			ra(stks);
		else
			pb(stks);
		i++;
	}
}

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

static void	sort_into_a(ssize_t **mc, t_stack stks[2])
{
	const t_idx_cost	cheapest = cheapest_idx(mc, stks[e_b].size);
	ssize_t				r_num[2] = {mc[e_topb][cheapest.idx],
						mc[e_desta][cheapest.idx]};
	ssize_t				double_r;
	ssize_t				total_r;
	void				(*ops[2])(t_stack[2]);
	ssize_t				i;

	double_r = 0;
	if (r_num[e_topb] > 0 && r_num[e_desta] > 0)
	{
		double_r = max(r_num[e_topb], r_num[e_desta]) - min(r_num[e_topb],
				r_num[e_desta]);
		ops[e_topb] = rr;
		ops[e_desta] = ra;
	}
	if (r_num[e_topb] < 0 && r_num[e_desta] < 0)
	{
		double_r = min(r_num[e_topb], r_num[e_desta]) - max(r_num[e_topb],
				r_num[e_desta]);
		ops[e_topb] = rrr;
		ops[e_desta] = rra;
	}
	if (double_r)
	{
		r_num[e_topb] = double_r;
		total_r = cheapest.idx;
		if (double_r < 0)
			total_r *= -1;
		r_num[e_topb] = total_r - double_r;
	}
	else
	{
		if (r_num[e_topb] > 0)
			ops[e_topb] = rb;
		else
			ops[e_topb] = rrb;
		if (r_num[e_desta] > 0)
			ops[e_desta] = ra;
		else
			ops[e_desta] = rrb;
	}
	i = ps_abs(r_num[e_topb]);
	while (i-- > 0)
		ops[e_topb](stks);
	i = ps_abs(r_num[e_desta]);
	while (i-- > 0)
		ops[e_desta](stks);
	pa(stks);
}

bool	sort(t_stack stks[2], bool verbose)
{
	ssize_t			**move_costs;
	const t_subseq	lis = lis_tabulation(stks[e_a]);

	if (!lis.seq)
		// TODO free
		return (false);
	push_non_lis(stks, lis);
	if (verbose)
		print_stacks(stks);
	while (stks[e_b].size)
	{
		move_costs = generate_costs(stks, verbose);
		if (!move_costs)
			return (false);
		sort_into_a(move_costs, stks);
	}
	return (true);
}
