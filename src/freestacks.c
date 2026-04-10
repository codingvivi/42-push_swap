/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestacks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:23:28 by lrain             #+#    #+#             */
/*   Updated: 2026/04/10 23:04:53 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freearr.h"
#include "stacks.h"
#include <stdlib.h>

void	free_stack(t_stack *sp)
{
	if (sp)
	{
		if (sp->data)
		{
			free(sp->data);
		}
		free(sp);
	}
}

void	free_stacks(t_stack *stks[2])
{
	free_stack(stks[e_a]);
	stks[e_a] = NULL;
	free_stack(stks[e_b]);
	stks[e_b] = NULL;
}
