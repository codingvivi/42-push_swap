/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:07:54 by lrain             #+#    #+#             */
/*   Updated: 2026/04/01 23:40:36 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "libft.h"
#include "push.h"
#include "rotate.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>

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

void	sort(t_stack stks[2])
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
#ifndef NDEBUG
	i = 0;
	ft_printf("after sort:\n");
	while (i < a->size)
	{
		ft_printf("%i ", a->data[from_head(*a, -i)]);
		i++;
	}
#endif
}
