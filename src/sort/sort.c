/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:07:54 by lrain             #+#    #+#             */
/*   Updated: 2026/04/08 01:16:50 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cost_ops.h"
#include "lis.h"
#include "print_stacks.h"
#include "push.h"
#include "rotate.h"
#include "stacks.h"
#include <stdbool.h>
#include <stdio.h>

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

//  static size_t cheapest_move(ssize_t mc)
// {

// }

bool	sort(t_stack stks[2], bool verbose)
{
	ssize_t			**move_costs;
	const t_subseq	lis = lis_tabulation(stks[e_a]);

	if (!lis.seq)
		return (false);
	push_non_lis(stks, lis);
	if (verbose)
		print_stacks(stks);
	// while (stks[e_b].size)
	// {
	move_costs = generate_costs(stks, verbose);
	if (!move_costs)
		return (false);
	// }
	return (true);
}
