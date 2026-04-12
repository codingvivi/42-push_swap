/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freecharr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:46:17 by lrain             #+#    #+#             */
/*   Updated: 2026/04/10 23:07:30 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	freecharr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free((void *)arr);
		arr = NULL;
	}
}
