/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 00:39:17 by lrain             #+#    #+#             */
/*   Updated: 2026/04/10 22:57:10 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freecharr.h"
#include "freestacks.h"
#include "libft.h"
#include "safe_ft_atoi.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

t_stack	*init_stack(size_t cap)
{
	t_stack	*sp;

	sp = malloc(sizeof(t_stack));
	if (!sp)
		return (NULL);
	*sp = (t_stack){.data = malloc(cap * sizeof(int)), .head = 0, .size = 0,
		.cap = cap};
	if (!sp->data)
	{
		free_stack(sp);
		sp = NULL;
	}
	return (sp);
}

bool	init_ab(size_t stk_size, t_stack *stks[2])
{
	stks[e_a] = init_stack(stk_size);
	if (!stks[e_a])
		return (false);
	stks[e_b] = init_stack(stk_size);
	if (!stks[e_b])
	{
		free_stack(stks[e_a]);
		stks[e_a] = NULL;
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
	if (!usr_in)
		return (false);
	i = 0;
	while (i < a->cap)
	{
		if (!safe_ft_atoi(usr_in[i], &a->data[a->cap - 1 - i]))
		{
			if (argc == 2)
			{
				freecharr(usr_in);
				usr_in = NULL;
			}
			return (false);
		}
		i++;
	}
	if (argc == 2)
	{
		freecharr(usr_in);
		usr_in = NULL;
	}
	a->head = a->cap - 1;
	a->size = a->cap;
	return (true);
}

bool	init_a(int argc, char **argv, t_stack *stks[2], bool *verbose)
{
	if (!parse_args(argc, argv, stks[e_a], verbose))
	{
		free_stacks(stks);
		stks = NULL;
		return (false);
	}
	return (true);
}
