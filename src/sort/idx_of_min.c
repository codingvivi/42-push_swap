/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idx_of_min.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:20:37 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 18:40:50 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"

size_t	idx_of_min(const t_stack s)
{
	size_t	i;
	int		i_val;
	size_t	candidate;
	int		can_val;

	i = 0;
	candidate = i;
	can_val = s.data[from_head(s, -candidate)];
	while (i < s.size)
	{
		i_val = s.data[from_head(s, -i)];
		if (i_val < can_val)
		{
			candidate = i;
			can_val = s.data[from_head(s, -candidate)];
		}
		i++;
	}
	return (candidate);
}
