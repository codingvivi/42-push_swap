/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 00:39:17 by lrain             #+#    #+#             */
/*   Updated: 2026/04/03 22:52:06 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "safe_ft_atoi.h"
#include "stacks.h"
#include <stdbool.h>
#include <stdlib.h>

t_stack	init_stack(size_t cap)
{
	return ((t_stack){.data = malloc(cap * sizeof(int)), .head = 0, .size = 0,
		.cap = cap});
}

bool	init_ab(size_t stk_size, t_stack stks[2])
{
	stks[e_a] = init_stack(stk_size);
	if (!stks[e_a].data)
		return (1);
	stks[e_b] = init_stack(stk_size);
	if (!stks[e_b].data)
	{
		free(stks[e_a].data);
		return (false);
	}
	return (true);
}

static bool	parse_args(int argc, char **argv, t_stack *a, bool *verbose)
{
	char	**usr_in;
	size_t	i;

	(void)verbose;
#ifndef NDEBUG
	if (argc > 1 && (!ft_strncmp(argv[1], "-v", 3) || !ft_strncmp(argv[1],
				"--verbose", 10)))
	{
		*verbose = true;
		argv++;
		argc--;
		a->cap--;
	}
#endif
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
	return (true);
}

bool	init_a(int argc, char **argv, t_stack *a, bool *verbose)
{
	size_t	i;

	if (!parse_args(argc, argv, a, verbose))
		return (false);
	if (*verbose)
	{
		ft_printf("arguments:\n");
		i = -1;
		while (++i < a->cap)
			ft_printf("%i ", a->data[i]);
		ft_printf("\n");
	}
	return (true);
}
