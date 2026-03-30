/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:51:34 by lrain             #+#    #+#             */
/*   Updated: 2026/03/30 22:31:16 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"
#include <stdbool.h>

static void	push(t_stack stgt, t_stack ssrc)
{
	if (!ssrc.size)
		return ;
	stgt.data[++stgt.head % stgt.size] = ssrc.data[ssrc.head--];
	ssrc.head %= ssrc.size;
	stgt.size++;
	ssrc.size--;
}
void	pa(t_stack stks[2])
{
	push(stks[e_a], stks[e_b]);
}

void	pb(t_stack stks[2])
{
	push(stks[e_b], stks[e_a]);
}
