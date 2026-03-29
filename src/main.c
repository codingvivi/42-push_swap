/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:26:20 by lrain             #+#    #+#             */
/*   Updated: 2026/03/29 18:54:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

bool	is_only_digits(char **arr);

int	main(int argc, char **argv)
{
	if (argc < 2 || !is_only_digits(++argv))
	{
		ft_printf("Error\n");
		return (1);
	}
	ft_printf("%s", argv);
	return (0);
}

bool	is_only_digits(char **arr)
{
	char	*curr_c;

	while (*arr)
	{
		curr_c = *arr;
		while (*curr_c)
		{
			if (!ft_isdigit(*curr_c++))
				return (false);
		}
		arr++;
	}
	return (true);
}
