/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:40:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/07 17:52:59 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_idx.h"
#include "libft.h"
#include "stacks.h"
#include <stddef.h>

void	print_stacks(t_stack stks[2])
{
	const t_stack	*a = &stks[e_a];
	const t_stack	*b = &stks[e_b];
	size_t			i;

	i = 0;
	ft_printf("after sort:\n");
	while (i < a->size)
		ft_printf("%i ", a->data[from_head(*a, -i++)]);
	i = 0;
	ft_printf("\nafter sort:\n");
	while (i < b->size)
		ft_printf("%i ", b->data[from_head(*b, -i++)]);
}
