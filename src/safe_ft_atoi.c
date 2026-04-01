/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:05:49 by lrain             #+#    #+#             */
/*   Updated: 2026/04/01 16:48:29 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdbool.h"
#include <limits.h>

static int	ft_isspace(int i)
{
	unsigned int		temp;
	const unsigned int	range = '\r' - '\t';

	temp = (unsigned)i;
	temp -= '\t';
	return (temp <= range || i == ' ');
}

static int	safe_converter(const char **sp, int **np, const int neg)
{
	bool	has_digit;

	has_digit = false;
	if (ft_isdigit(**sp))
		has_digit = true;
	while (ft_isdigit(**sp))
	{
		if (**np < (INT_MIN + (**sp - '0')) / 10)
			return (1);
		**np = (10 * (**np)) - (*(*sp)++ - '0');
	}
	if (!neg)
		**np *= -1;
	if (!has_digit)
		return (1);
	if (!ft_isspace(**sp) && **sp != '\0')
		return (1);
	return (0);
}

int	safe_ft_atoi(const char *str, int *nb)
{
	int	neg;

	*nb = 0;
	neg = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	return (safe_converter(&str, &nb, neg));
}
