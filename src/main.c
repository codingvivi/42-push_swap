/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:26:20 by lrain             #+#    #+#             */
/*   Updated: 2026/04/10 23:08:49 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freestacks.h"
#include "get_args.h"
#include "init.h"
#include "libft.h"
#include "print_stacks.h"
#include "sort.h"
#include "stacks.h"
#include <stdbool.h>

static int	end_w_err(void);

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
