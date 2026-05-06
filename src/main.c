/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:26:20 by lrain             #+#    #+#             */
/*   Updated: 2026/05/06 17:29:21 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freecharr.h"
#include "freestacks.h"
#include "get_args.h"
#include "get_idx.h"
#include "init.h"
#include "libft.h"
#include "print_stacks.h"
#include "sort.h"
#include "stacks.h"
#include <stdbool.h>

static int		end_w_err(void);
static bool		issorted(t_stack *a);
static size_t	get_stack_size(int argc, char **argv);

int	main(int argc, char **argv)
{
	const size_t	stack_size = get_stack_size(argc, argv);
	t_stack			*stacks[2];
	bool			verbose;

	verbose = false;
	if (argc < 2 || stack_size == 0)
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

static size_t	get_stack_size(int argc, char **argv)
{
	char	**split;
	size_t	count;
	int		start;

	if (argc < 2)
		return (0);
	start = 1;
	if (PS_DEBUG && (ft_strncmp(argv[1], "-v", 3) == 0 || ft_strncmp(argv[1],
				"--verbose", 10) == 0))
		start = 2;
	if (argc - start < 1)
		return (0);
	if (argc - start > 1)
		return (argc - start);
	split = ft_split(argv[start], ' ');
	if (!split)
		return (0);
	count = 0;
	while (split[count])
		count++;
	freecharr(split);
	return (count);
}
