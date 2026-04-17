/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/17 16:00:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_final_idxs.h"
#include "reverse_rotate.h"
#include "rotate.h"
#include "sort_3.h"
#include "stacks.h"
#include "swap.h"
#include <stdbool.h>
#include <stddef.h>

static void	algo_3(t_stack *stks[2], size_t top, size_t mid, size_t bot)
{
	if (top > mid && top > bot)
	{
		if (mid < bot)
			ra(stks);
		else
		{
			ra(stks);
			sa(stks);
		}
	}
	else if (mid > bot)
	{
		if (top < bot)
		{
			sa(stks);
			ra(stks);
		}
		else
			rra(stks);
	}
	else if (top > mid)
		sa(stks);
}

bool	sort_3(t_stack *stks[2])
{
	const size_t	*final_idxs = get_final_idxs(stks[e_a]);

	if (!final_idxs)
		return (false);
	algo_3(stks, final_idxs[0], final_idxs[1], final_idxs[2]);
	return (true);
}
