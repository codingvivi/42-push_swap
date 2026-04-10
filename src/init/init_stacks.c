/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 00:39:17 by lrain             #+#    #+#             */
/*   Updated: 2026/04/11 00:00:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freestacks.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

t_stack	*init_stack(size_t cap)
{
	t_stack	*sp;

	sp = malloc(sizeof(t_stack));
	if (!sp)
		return (NULL);
	*sp = (t_stack){.data = malloc(cap * sizeof(int)), .head = 0, .size = 0,
		.cap = cap};
	if (!sp->data)
	{
		free_stack(sp);
		sp = NULL;
	}
	return (sp);
}

bool	init_ab(size_t stk_size, t_stack *stks[2])
{
	stks[e_a] = init_stack(stk_size);
	if (!stks[e_a])
		return (false);
	stks[e_b] = init_stack(stk_size);
	if (!stks[e_b])
	{
		free_stack(stks[e_a]);
		stks[e_a] = NULL;
		return (false);
	}
	return (true);
}
