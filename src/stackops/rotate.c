/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:02:46 by lrain             #+#    #+#             */
/*   Updated: 2026/03/31 20:39:46 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "libft.h"
#include "stacks.h"

/*
 Array:  [ 1 | 2 | 3 | _ | _ ] head at 3
 We need to keep fields to the right of head free
 in case of pushes.
 Head is included in count
 thus size is one behind tail.
 After rotate:
 Array:  [ 1 | 2 | _ | _ | 3 ] head at 2
*/
static void	rotate(t_stack *s)
{
	s->data[from_head(*s, -s->size)] = s->data[s->head];
	s->head = from_head(*s, -1);
}

void	ra(t_stack *stks[2])
{
	rotate(stks[e_a]);
	ft_printf("ra\n");
}

void	rb(t_stack *stks[2])
{
	rotate(stks[e_b]);
	ft_printf("rb\n");
}

void	rr(t_stack *stks[2])
{
	rotate(stks[e_a]);
	rotate(stks[e_b]);
	ft_printf("rr\n");
}
