/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_idxs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:26:34 by lrain             #+#    #+#             */
/*   Updated: 2026/04/17 15:00:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static bool	bubble_pass(int *sd, size_t size)
{
	size_t	j;
	int		buf;
	bool	swapped;

	j = 0;
	swapped = false;
	while (j < size - 1)
	{
		if (sd[j] > sd[j + 1])
		{
			buf = sd[j];
			sd[j] = sd[j + 1];
			sd[j + 1] = buf;
			swapped = true;
		}
		j++;
	}
	return (swapped);
}

static void	bubble_sort(int *sd, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1)
	{
		if (!bubble_pass(sd, size - i))
			break ;
		i++;
	}
}

static int	*get_sorted_copy(const t_stack *a)
{
	int		*sd;
	size_t	i;

	sd = malloc(a->size * sizeof(int));
	if (!sd)
		return (NULL);
	i = 0;
	while (i < a->size)
	{
		sd[i] = a->data[from_head(*a, -i)];
		i++;
	}
	bubble_sort(sd, a->size);
	return (sd);
}

static size_t	*find_idxs(const t_stack *a, const int *sd)
{
	size_t	*fi;
	size_t	i_a;
	size_t	i_sd;

	fi = malloc(a->size * sizeof(size_t));
	if (!fi)
		return (NULL);
	i_a = 0;
	while (i_a < a->size)
	{
		i_sd = 0;
		while (i_sd < a->size)
		{
			if (a->data[from_head(*a, -i_a)] == sd[i_sd])
			{
				fi[i_a] = i_sd;
				break ;
			}
			i_sd++;
		}
		i_a++;
	}
	return (fi);
}

size_t	*get_final_idxs(const t_stack *a)
{
	int		*sorted_data;
	size_t	*final_idxs;

	sorted_data = get_sorted_copy(a);
	if (!sorted_data)
		return (NULL);
	final_idxs = find_idxs(a, sorted_data);
	free(sorted_data);
	return (final_idxs);
}
