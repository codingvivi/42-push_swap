/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freearr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:16:15 by lrain             #+#    #+#             */
/*   Updated: 2026/04/10 19:40:50 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freearr.h"
#include "stdlib.h"

void	freearr(void **arr, size_t len, t_free_membr_fn freefn)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (i < len)
		{
			if (arr[i])
			{
				freefn(arr[i]);
				arr[i] = NULL;
			}
			i++;
		}
		free(arr);
	}
}
