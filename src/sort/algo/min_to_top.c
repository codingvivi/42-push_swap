/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_to_top.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:45:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 20:45:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cost_ops.h"
#include "idx_of_min.h"
#include "pickop.h"
#include "stacks.h"
#include "value_fetchers.h"
#include <stddef.h>
#include <sys/types.h>

void	min_to_top(t_stack *stks[2])
{
	const t_stack	a = *stks[e_a];
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
