/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:26:20 by lrain             #+#    #+#             */
/*   Updated: 2026/04/12 02:54:06 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freestacks.h"
#include "get_args.h"
#include "get_idx.h"
#include "init.h"
#include "libft.h"
#include "print_stacks.h"
#include "sort.h"
#include "stacks.h"
#include <stdbool.h>

static int	end_w_err(void);
static bool	issorted(t_stack *a);

int	main(int argc, char **argv)
{
	size_t	stack_size;
	t_stack	*stacks[2];
	bool	verbose;

	verbose = false;
	stack_size = argc - 1;
	if (argc < 2)
		return (end_w_err());
	if (!init_ab(stack_size, stacks))
		return (end_w_err());
	if (!get_args(argc, argv, stacks, &verbose))
		return (end_w_err());
	if (verbose)
		print_stacks(stacks);
	if (issorted(stacks[e_a]))
	{
		free_stacks(stacks);
		return (0);
	}
	if (!sort(stacks, verbose))
	{
		free_stacks(stacks);
		return (end_w_err());
	}
	free_stacks(stacks);
	return (0);
}

static int	end_w_err(void)
{
	ft_putstr_fd("Error\n", 2);
	return (1);
}

static bool	issorted(t_stack *a)
{
	size_t	i;

	if (a->size < 2)
		return (true);
	i = 0;
	while (i < a->size - 1)
	{
		if (a->data[from_head(*a, -i - 1)] < a->data[from_head(*a, -i)])
			return (false);
		i++;
	}
	return (true);
}
