/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:51:34 by lrain             #+#    #+#             */
/*   Updated: 2026/03/31 20:39:25 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "libft.h"
#include "stacks.h"
#include <stdbool.h>

static void	push(t_stack *stgt, t_stack *ssrc)
{
	if (!ssrc->size)
		return ;
	stgt->head = from_head(*stgt, +1);
	stgt->size++;
	stgt->data[stgt->head] = ssrc->data[ssrc->head];
	ssrc->head = from_head(*ssrc, +1);
	ssrc->size--;
}

void	pa(t_stack stks[2])
{
	push(&stks[e_a], &stks[e_b]);
	ft_printf("pa\n");
}

void	pb(t_stack stks[2])
{
	push(&stks[e_b], &stks[e_a]);
	ft_printf("pb\n");
}
