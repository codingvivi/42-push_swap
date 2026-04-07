/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:26:20 by lrain             #+#    #+#             */
/*   Updated: 2026/04/04 01:35:48 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "libft.h"
#include "sort.h"
#include "stacks.h"
#include <stdbool.h>

static int	end_w_err(void);

int	main(int argc, char **argv)
{
	size_t	stack_size;
	t_stack	stacks[2];
	bool	verbose;

	verbose = false;
	stack_size = argc - 1;
	if (argc < 2)
		return (end_w_err());
	if (!init_ab(stack_size, stacks))
		return (end_w_err());
	if (!init_a(argc, argv, &stacks[e_a], &verbose))
		return (end_w_err());
	sort(stacks, verbose);
	return (0);
}

static int	end_w_err(void)
{
	ft_putstr_fd("Error\n", 2);
	return (1);
}
