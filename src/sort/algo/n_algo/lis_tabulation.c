/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_tabulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/18 15:30:38 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "stacks.h"
#include <stddef.h>
#include <stdlib.h>

static void			fill_len(const t_stack *s, size_t *len, ssize_t *prev);
static t_idx_len	find_max_len(const size_t *len, size_t n);
static t_subseq		backtrack(const t_stack *s, const size_t *len,
						const ssize_t *prev);

t_subseq	lis_tabulation(const t_stack *s)
{
	size_t		*len;
	ssize_t		*prev;
	t_subseq	result;

	if (s->size == 0)
		return ((t_subseq){NULL, 0});
	len = malloc(s->size * sizeof(size_t));
	if (!len)
		return ((t_subseq){NULL, 0});
	prev = malloc(s->size * sizeof(ssize_t));
	if (!prev)
	{
		free(len);
		return ((t_subseq){NULL, 0});
	}
	fill_len(s, len, prev);
	result = backtrack(s, len, prev);
	free(len);
	free(prev);
	return (result);
}

/*
runs through array for each index
checks if there is a smaller number
and if it is part of a subsequence equal or bigger.
if so
sets the subsequence of the current index as that +1
and sets the previous item
*/
static void	fill_len(const t_stack *s, size_t *len, ssize_t *prev)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < s->size)
	{
		len[i] = 1;
		prev[i] = -1;
		j = 0;
		while (j < i)
		{
			if (s->data[from_head(*s, -j)] < s->data[from_head(*s, -i)]
				&& len[j] + 1 > len[i])
			{
				len[i] = len[j] + 1;
				prev[i] = j;
			}
			j++;
		}
		i++;
	}
}

static t_idx_len	find_max_len(const size_t *len, size_t n)
{
	t_idx_len	best;
	size_t		i;

	best.len = 0;
	best.idx = 0;
	i = 0;
	while (i < n)
	{
		if (len[i] > best.len)
		{
			best.len = len[i];
			best.idx = i;
		}
		i++;
	}
	return (best);
}

static t_subseq	backtrack(const t_stack *s, const size_t *len,
		const ssize_t *prev)
{
	const t_idx_len	best = find_max_len(len, s->size);
	ssize_t			idx;
	size_t			i;
	int				*seq;

	seq = malloc(sizeof(int) * best.len);
	if (!seq)
		return ((t_subseq){NULL, 0});
	idx = best.idx;
	i = best.len - 1;
	while (idx != -1)
	{
		seq[i--] = s->data[from_head(*s, -idx)];
		idx = prev[idx];
	}
	return ((t_subseq){seq, best.len});
}
