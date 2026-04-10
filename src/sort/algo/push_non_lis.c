/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_non_lis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 23:34:32 by lrain             #+#    #+#             */
/*   Updated: 2026/04/11 01:33:59 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freearr.h"
#include "get_idx.h"
#include "push.h"
#include "rotate.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

t_subseq	lis_tabulation(const t_stack *s)
{
	const size_t	n = s->size;
	size_t			dp[n];
	ssize_t			parent[n];
	size_t			max_len;
	ssize_t			max_idx;
	ssize_t			idx;
	size_t			i;
	int				*seq;

	if (n == 0)
		return ((t_subseq){NULL, 0});
	for (i = 0; i < n; i++)
	{
		dp[i] = 1;
		parent[i] = -1;
		for (size_t j = 0; j < i; j++)
		{
			if (s->data[from_head(*s, -j)] < s->data[from_head(*s, -i)] && dp[j]
				+ 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
				parent[i] = j;
			}
		}
	}
	max_len = 0;
	max_idx = 0;
	for (i = 0; i < n; i++)
	{
		if (dp[i] > max_len)
		{
			max_len = dp[i];
			max_idx = i;
		}
	}
	seq = malloc(sizeof(int) * max_len);
	if (!seq)
		return ((t_subseq){NULL, 0});
	idx = max_idx;
	i = max_len - 1;
	while (idx != -1)
	{
		seq[i--] = s->data[from_head(*s, -idx)];
		idx = parent[idx];
	}
	return ((t_subseq){seq, max_len});
}

static void	push_or_rotate(t_stack *stks[2], t_subseq lis)
{
	const t_stack	*a = stks[e_a];
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

bool	push_non_lis(t_stack *stks[2])
{
	const t_subseq	lis = lis_tabulation(stks[e_a]);

	if (!lis.seq)
		return (false);
	push_or_rotate(stks, lis);
	free(lis.seq);
	return (true);
}
