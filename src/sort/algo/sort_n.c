/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/17 16:00:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cost_ops.h"
#include "freearr.h"
#include "min_to_top.h"
#include "print_stacks.h"
#include "push_non_lis.h"
#include "sort_into_a.h"
#include "sort_n.h"
#include "stacks.h"
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

bool	sort_n(t_stack *stks[2], bool verbose)
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
		freearr((void **)move_costs, 2, &free);
		move_costs = NULL;
	}
	min_to_top(stks);
	if (verbose)
		print_stacks(stks);
	return (true);
}
