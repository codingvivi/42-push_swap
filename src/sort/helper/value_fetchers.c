/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_fetchers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:16:48 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 19:17:03 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

ssize_t	ps_abs(ssize_t nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}

ssize_t	max(ssize_t x, ssize_t y)
{
	if (x < y)
		x = y;
	return (x);
}

ssize_t	min(ssize_t x, ssize_t y)
{
	if (x > y)
		x = y;
	return (x);
}
