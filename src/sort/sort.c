/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:07:54 by lrain             #+#    #+#             */
/*   Updated: 2026/04/04 21:14:09 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "libft.h"
#include "lis.h"
#include "push.h"
#include "rotate.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool	is_empty(const t_stack s)
{
	if (s.size)
		return (false);
	return (true);
}

int	get_min(const t_stack s)
{
	size_t	i;
	int		min;
	int		curr;

	i = 0;
	min = s.data[s.head];
	while (i++ < s.size - 1)
	{
		curr = s.data[from_head(s, -i)];
		if (curr < min)
			min = curr;
	}
	return (min);
}
bool	sort(t_stack stks[2], bool verbose)
{
	const t_stack	*a = &stks[e_a];
	const t_stack	*b = &stks[e_b];
	const t_subseq	lis = lis_tabulation(stks[e_a]);
	const size_t	n = a->size;
	size_t			i;
	size_t			j;
	bool			is_lis;

	if (!lis.seq)
		return (false);
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
	};
	if (verbose)
	{
		i = 0;
		ft_printf("after sort:\n");
		while (i < a->size)
			ft_printf("%i ", a->data[from_head(*a, -i++)]);
		i = 0;
		ft_printf("\nafter sort:\n");
		while (i < b->size)
			ft_printf("%i ", b->data[from_head(*b, -i++)]);
	}
	return (true);
}

void	sort_old(t_stack stks[2], bool verbose)
{
	t_stack	*a;
	t_stack	*b;
	int		min;
	size_t	i;

	a = &stks[e_a];
	b = &stks[e_b];
	while (!is_empty(*a))
	{
		min = get_min(*a);
		while (a->data[a->head] != min)
			ra(stks);
		pb(stks);
	}
	while (!is_empty(*b))
		pa(stks);
	if (verbose)
	{
		i = 0;
		ft_printf("after sort:\n");
		while (i < a->size)
			ft_printf("%i ", a->data[from_head(*a, -i++)]);
	}
}
