/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 22:56:54 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 18:51:39 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "libft.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static ssize_t	**init_cost_arr(size_t size)
{
	ssize_t	**arr;
	size_t	i;

	arr = (ssize_t **)malloc(2 * sizeof(ssize_t *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i <= e_desta)
	{
		arr[i] = malloc(size * sizeof(ssize_t));
		// TODO free
		if (!arr[i])
			return (NULL);
		i++;
	}
	return (arr);
}

ssize_t	get_rotate_cost(size_t tgt_idx, size_t size)
{
	ssize_t	cost;

	if (tgt_idx <= ((size - 1) / 2))
		cost = tgt_idx;
	else
		cost = -(ssize_t)(size - tgt_idx);
	return (cost);
}

size_t	idx_of_min(const t_stack s)
{
	size_t	i;
	int		i_val;
	size_t	candidate;
	int		can_val;

	i = 0;
	candidate = i;
	can_val = s.data[from_head(s, -candidate)];
	while (i < s.size)
	{
		i_val = s.data[from_head(s, -i)];
		if (i_val < can_val)
		{
			candidate = i;
			can_val = s.data[from_head(s, -candidate)];
		}
		i++;
	}
	return (candidate);
}
static size_t	find_dest_idx(const t_stack a, int b_val)
{
	size_t	i;
	int		i_val;
	size_t	candidate;
	int		can_val;
	bool	found;

	i = 0;
	candidate = i;
	found = false;
	while (i < a.size)
	{
		i_val = a.data[from_head(a, -i)];
		if (i_val > b_val && (i_val < can_val || !found))
		{
			candidate = i;
			can_val = a.data[from_head(a, -candidate)];
			found = true;
		}
		i++;
	}
	if (!found)
		candidate = idx_of_min(a);
	return (candidate);
}

static void	write_costs(ssize_t **mc_p, const t_stack stks[2])
{
	const t_stack	a = stks[e_a];
	const t_stack	b = stks[e_b];
	size_t			i;

	i = 0;
	while (i < b.size)
	{
		mc_p[e_desta][i] = get_rotate_cost(find_dest_idx(a, b.data[from_head(b,
						-i)]), a.size);
		i++;
	}
	i = 0;
	while (i < b.size)
	{
		mc_p[e_topb][i] = get_rotate_cost(i, b.size);
		i++;
	}
}

ssize_t	**generate_costs(const t_stack stks[2], bool verbose)
{
	ssize_t	**costs;
	size_t	i;
	size_t	j;

	costs = init_cost_arr(stks[e_b].size);
	// TODO free
	if (!costs)
		return (NULL);
	write_costs(costs, stks);
	if (verbose)
	{
		i = 0;
		while (i <= e_desta)
		{
			j = 0;
			while (j < stks[e_b].size)
			{
				ft_printf("%i\n", costs[i][j]);
				j++;
			}
			ft_printf("\n\n");
			i++;
		}
	}
	return (costs);
}
