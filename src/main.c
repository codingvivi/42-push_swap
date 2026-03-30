/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:26:20 by lrain             #+#    #+#             */
/*   Updated: 2026/03/30 19:36:36 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
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
	stacks[e_a] = (t_stack){.data = malloc(stack_size * sizeof(int)), .tail = 0,
		.head = stack_size};
	if (!stacks[e_a].data)
		return (1);
	i = 0;
	while (i <= max_i)
	{
		stacks[e_a].data[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	stacks[e_b] = (t_stack){.data = malloc(stack_size * sizeof(int)), .tail = 0,
		.head = stack_size};
	if (!stacks[e_b].data)
		return (1);
	i = 0;
	while (i <= max_i)
		ft_printf("%i\n", stacks[e_a].data[i++]);
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
