/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_tabulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/11 00:00:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "stacks.h"
#include <stddef.h>
#include <stdlib.h>

static void			fill_dp(const t_stack *s, size_t *dp, ssize_t *parent);
static t_idx_cost	find_max_dp(const size_t *dp, size_t n);
static t_subseq		backtrack(const t_stack *s, const size_t *dp,
						const ssize_t *parent);

t_subseq	lis_tabulation(const t_stack *s)
{
	size_t		*dp;
	ssize_t		*parent;
	t_subseq	result;

	if (s->size == 0)
		return ((t_subseq){NULL, 0});
	dp = malloc(s->size * sizeof(size_t));
	if (!dp)
		return ((t_subseq){NULL, 0});
	parent = malloc(s->size * sizeof(ssize_t));
	if (!parent)
	{
		free(dp);
		return ((t_subseq){NULL, 0});
	}
	fill_dp(s, dp, parent);
	result = backtrack(s, dp, parent);
	free(dp);
	free(parent);
	return (result);
}

static void	fill_dp(const t_stack *s, size_t *dp, ssize_t *parent)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < s->size)
	{
		dp[i] = 1;
		parent[i] = -1;
		j = 0;
		while (j < i)
		{
			if (s->data[from_head(*s, -j)] < s->data[from_head(*s, -i)] && dp[j]
				+ 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
				parent[i] = j;
			}
			j++;
		}
		i++;
	}
}

static t_idx_cost	find_max_dp(const size_t *dp, size_t n)
{
	t_idx_cost	best;
	size_t		i;

	best.cost = 0;
	best.idx = 0;
	i = 0;
	while (i < n)
	{
		if ((size_t)dp[i] > (size_t)best.cost)
		{
			best.cost = dp[i];
			best.idx = i;
		}
		i++;
	}
	return (best);
}

static t_subseq	backtrack(const t_stack *s, const size_t *dp,
		const ssize_t *parent)
{
	const t_idx_cost	best = find_max_dp(dp, s->size);
	ssize_t				idx;
	size_t				i;
	int					*seq;

	seq = malloc(sizeof(int) * best.cost);
	if (!seq)
		return ((t_subseq){NULL, 0});
	idx = best.idx;
	i = best.cost - 1;
	while (idx != -1)
	{
		seq[i--] = s->data[from_head(*s, -idx)];
		idx = parent[idx];
	}
	return ((t_subseq){seq, best.cost});
}
