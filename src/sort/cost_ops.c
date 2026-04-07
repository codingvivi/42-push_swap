/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 22:56:54 by lrain             #+#    #+#             */
/*   Updated: 2026/04/08 00:40:17 by lrain            ###   ########.fr       */
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
	while (i <= e_dest_a)
	{
		arr[i] = malloc(size * sizeof(ssize_t));
		// TODO free
		if (!arr[i])
			return (NULL);
		i++;
	}
	return (arr);
}

static ssize_t	get_cost(size_t tgt_idx, size_t size)
{
	ssize_t	cost;

	if (tgt_idx <= ((size - 1) / 2))
		cost = tgt_idx;
	else
		cost = -(ssize_t)(size - tgt_idx);
	return (cost);
}

static void	write_costs(ssize_t **mc_p, const t_stack stks[2])
{
	const t_stack	a = stks[e_a];
	const t_stack	b = stks[e_b];
	size_t			i;
	size_t			idx_a;

	i = 0;
	while (i < b.size)
	{
		idx_a = 0;
		while (idx_a < a.size)
		{
			if (a.data[from_head(a, -idx_a)] > b.data[from_head(b, -i)])
				break ;
			idx_a++;
		}
		mc_p[e_dest_a][i] = get_cost(idx_a, a.size);
		i++;
	}
	i = 0;
	while (i < b.size)
	{
		mc_p[e_top_b][i] = get_cost(i, b.size);
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
		while (i <= e_dest_a)
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
