/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestacks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:23:28 by lrain             #+#    #+#             */
/*   Updated: 2026/04/10 20:23:28 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freearr.h"
#include "stacks.h"
#include <stdlib.h>

void	free_stack(t_stack *sp)
{
	if (sp)
	{
		if (!sp->data)
		{
			free(sp->data);
		}
		free(sp);
		sp = NULL;
	}
}

void	free_stacks(t_stack *stks[2])
{
	freearr((void **)stks, 2, (t_free_membr_fn)&free_stack);
}
