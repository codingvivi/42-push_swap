/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:21:33 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 19:23:31 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pickop.h"
#include "reverse_rotate.h"
#include "rotate.h"

t_op	pick_b(ssize_t n)
{
	if (n < 0)
		return (rrb);
	return (rb);
}

t_op	pick_a(ssize_t n)
{
	if (n < 0)
		return (rra);
	return (ra);
}

t_op	pick_both(ssize_t n)
{
	if (n < 0)
		return (rrr);
	return (rr);
}
