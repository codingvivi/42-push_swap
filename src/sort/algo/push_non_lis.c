/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_non_lis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 23:34:32 by lrain             #+#    #+#             */
/*   Updated: 2026/04/11 18:13:32 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lis_tabulation.h"
#include "push.h"
#include "rotate.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static bool	is_in_lis(int val, t_subseq lis);
static void	push_or_rotate(t_stack *stks[2], t_subseq lis);

bool	push_non_lis(t_stack *stks[2])
{
	const t_subseq	lis = lis_tabulation(stks[e_a]);

	if (!lis.seq)
		return (false);
	push_or_rotate(stks, lis);
	free(lis.seq);
	return (true);
}

static bool	is_in_lis(int val, t_subseq lis)
{
	size_t	j;

	j = 0;
	while (j < lis.size)
	{
		if (val == lis.seq[j])
			return (true);
		j++;
	}
	return (false);
}

static void	push_or_rotate(t_stack *stks[2], t_subseq lis)
{
	const t_stack	*a = stks[e_a];
	const size_t	n = a->size;
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (is_in_lis(a->data[a->head], lis))
			ra(stks);
		else
			pb(stks);
		i++;
	}
}
