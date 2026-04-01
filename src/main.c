/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:26:20 by lrain             #+#    #+#             */
/*   Updated: 2026/04/01 18:59:53 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "safe_ft_atoi.h"
#include "stacks.h"
#include <stdbool.h>
#include <stdlib.h>

static t_stack	init_stack(size_t cap)
{
	return ((t_stack){.data = malloc(cap * sizeof(int)), .head = 0, .size = 0,
		.cap = cap});
}

static bool	parse_args(int argc, char **argv, t_stack *a)
{
	char	**usr_in;
	size_t	i;

	if (argc == 2)
		usr_in = ft_split(argv[1], ' ');
	else
		usr_in = (argv + 1);
	i = 0;
	while (i < a->cap)
	{
		if (!safe_ft_atoi(usr_in[i], &a->data[i]))
			return (false);
		a->head = i++;
		a->size = i;
	}
#ifndef NDEBUG
	ft_printf("arguments:\n");
	i = 0;
	while (i < a->cap)
		ft_printf("%i\n", a->data[i++]);
#endif
	return (true);
}

int	main(int argc, char **argv)
{
	const size_t	stack_size = argc - 1;
	t_stack			stacks[2];

	if (argc < 2)
	{
		ft_printf("Error\n");
		return (1);
	}
	stacks[e_a] = init_stack(stack_size);
	if (!stacks[e_a].data)
		return (1);
	stacks[e_b] = init_stack(stack_size);
	if (!stacks[e_b].data)
	{
		free(stacks[e_a].data);
		return (1);
	}
	if (!parse_args(argc, argv, &stacks[e_a]))
	{
		ft_printf("Error\n");
		return (1);
	}
	return (0);
}
