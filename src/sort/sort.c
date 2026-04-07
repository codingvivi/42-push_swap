/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:07:54 by lrain             #+#    #+#             */
/*   Updated: 2026/04/07 17:52:58 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "libft.h"
#include "lis.h"
#include "print_stacks.h"
#include "push.h"
#include "rotate.h"
#include "stacks.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void	move_non_lis(t_stack stks[2], t_subseq lis)
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

static ssize_t	**init_cost_arr(size_t size)
{
	ssize_t	**move_costs;
	size_t	i;

	move_costs = (ssize_t **)malloc(2 * sizeof(ssize_t *));
	if (!move_costs)
		return (NULL);
	i = 0;
	while (i <= e_b)
	{
		move_costs[i] = malloc(size * sizeof(ssize_t));
		if (!move_costs[i])
			return (NULL);
		i++;
	}
	return (move_costs);
}

static ssize_t	get_cost(size_t idx, size_t size)
{
	ssize_t	cost;

	if ((idx <= size - 1) / 2)
		cost = idx;
	else
		cost = -(ssize_t)(size - idx);
	return (cost);
}

static void	write_costs(ssize_t **mc, t_stack stks[2])
{
	const t_stack	a = stks[e_a];
	const t_stack	b = stks[e_b];
	size_t			i;
	size_t			i_a;

	i = 0;
	while (i < b.size)
		mc[e_b][i] = get_cost(i, b.size);
	i = 0;
	while (i < b.size)
	{
		i_a = 0;
		while (i_a < a.size)
		{
			if (a.data[from_head(a, -i_a)] > b.data[from_head(b, -i)])
				break ;
			i_a++;
		}
		mc[e_a][i] = i_a;
		i++;
	}
}

bool	sort(t_stack stks[2], bool verbose)
{
	const t_subseq	lis = lis_tabulation(stks[e_a]);
	ssize_t			**move_costs;

	if (!lis.seq)
		return (false);
	move_non_lis(stks, lis);
	if (verbose)
		print_stacks(stks);
	move_costs = init_cost_arr(stks[e_b].size);
	if (!move_costs)
		return (false);
	write_costs(move_costs, stks);
	return (true);
}
