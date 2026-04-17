/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_4or5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:15:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/17 16:15:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "idx_of_min.h"
#include "push.h"
#include "reverse_rotate.h"
#include "rotate.h"
#include "sort_3.h"
#include "sort_4or5.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>

static void	push_min_to_b(t_stack *stks[2])
{
	size_t	idx;
	size_t	size;

	idx = idx_of_min(*stks[e_a]);
	size = stks[e_a]->size;
	if (idx <= size / 2)
		while (idx--)
			ra(stks);
	else
		while (idx++ < size)
			rra(stks);
	pb(stks);
}

bool	sort_4or5(t_stack *stks[2])
{
	bool	is_five;

	is_five = (stks[e_a]->size == 5);
	push_min_to_b(stks);
	if (is_five)
		push_min_to_b(stks);
	if (!sort_3(stks))
		return (false);
	pa(stks);
	if (is_five)
		pa(stks);
	return (true);
}
