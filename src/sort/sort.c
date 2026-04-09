/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:07:54 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 19:00:50 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cost_ops.h"
#include "idx_of_min.h"
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

typedef void		(*t_op)(t_stack[2]);

static t_op	pick_b(ssize_t n)
{
	if (n < 0)
		return (rrb);
	return (rb);
}

static t_op	pick_a(ssize_t n)
{
	if (n < 0)
		return (rra);
	return (ra);
}

static t_op	pick_both(ssize_t n)
{
	if (n < 0)
		return (rrr);
	return (rr);
}

static void	sort_into_a(ssize_t **mc, t_stack stks[2])
{
	const t_idx_cost	cheap = cheapest_idx(mc, stks[e_b].size);
	const ssize_t		rb_n = mc[e_topb][cheap.idx];
	const ssize_t		ra_n = mc[e_desta][cheap.idx];
	t_op				op_b;
	t_op				op_a;
	t_op				op_both;
	ssize_t				mag_b;
	ssize_t				mag_a;
	ssize_t				both;

	op_b = pick_b(rb_n);
	op_a = pick_a(ra_n);
	op_both = NULL;
	mag_b = ps_abs(rb_n);
	mag_a = ps_abs(ra_n);
	both = 0;
	if ((rb_n < 0) == (ra_n < 0) && rb_n && ra_n)
	{
		op_both = pick_both(rb_n);
		both = min(mag_a, mag_b);
		mag_a -= both;
		mag_b -= both;
	}
	while (both-- > 0)
		op_both(stks);
	while (mag_b-- > 0)
		op_b(stks);
	while (mag_a-- > 0)
		op_a(stks);
	pa(stks);
}

static void	min_to_top(t_stack stks[2])
{
	const t_stack	a = stks[e_a];
	const size_t	idx_min = idx_of_min(a);
	size_t			rotates;
	ssize_t			r_cost;
	t_op			op;

	if (idx_min != 0)
	{
		r_cost = get_rotate_cost(idx_min, a.size);
		op = pick_a(r_cost);
		rotates = ps_abs(r_cost);
		while (rotates--)
			op(stks);
	}
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
	min_to_top(stks);
	if (verbose)
		print_stacks(stks);
	return (true);
}
