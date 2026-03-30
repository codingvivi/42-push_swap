/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:26:20 by lrain             #+#    #+#             */
/*   Updated: 2026/03/30 22:54:41 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stacks.h"
#include <stdbool.h>
#include <stdlib.h>

bool	is_only_digits(char **arr);

int	main(int argc, char **argv)
{
	const size_t	stack_size = argc - 1;
	const size_t	max_i = stack_size - 1;
	t_stack			stacks[2];
	size_t			i;

	if (argc < 2 || !is_only_digits(argv + 1))
	{
		ft_printf("Error\n");
		return (1);
	}
	// init
	// a
	stacks[e_a] = (t_stack){.data = malloc(stack_size * sizeof(int))};
	if (!stacks[e_a].data)
		return (1);
	stacks[e_a] = (t_stack){.head = 0, .size = 0};
	// b
	stacks[e_b] = (t_stack){.data = malloc(stack_size * sizeof(int))};
	if (!stacks[e_b].data)
	{
		free(stacks[e_a].data);
		stacks[e_a].data = 0;
		return (1);
	}
	stacks[e_b] = (t_stack){.head = 0, .size = 0};
	// write args
	i = 0;
	while (i <= max_i)
	{
		stacks[e_a].data[i] = ft_atoi(argv[i + 1]);
		stacks[e_a].head = i++;
		stacks[e_a].size = i;
	}
#ifndef NDEBUG
	while (i <= max_i)
	{
		ft_printf("arguments:");
		ft_printf("%i\n", stacks[e_a].data[i++]);
	}
#endif
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
