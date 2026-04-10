/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:07:54 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 20:19:46 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cost_ops.h"
#include "min_to_top.h"
#include "print_stacks.h"
#include "push_non_lis.h"
#include "sort_into_a.h"
#include "stacks.h"
#include <stdbool.h>
#include <sys/types.h>

bool	sort(t_stack *stks[2], bool verbose)
{
	ssize_t	**move_costs;

	if (!push_non_lis(stks))
		return (false);
	if (verbose)
		print_stacks(stks);
	while (stks[e_b]->size)
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
