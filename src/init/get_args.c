/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/12 02:35:34 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freecharr.h"
#include "freestacks.h"
#include "get_idx.h"
#include "libft.h"
#include "safe_ft_atoi.h"
#include "stacks.h"
#include <stdbool.h>
#include <stddef.h>

static void	parse_verbose(int *argc, char ***argv, t_stack *a, bool *verbose);
static bool	write_args(char **usr_in, t_stack *a, int argc);
static bool	parse_args(int argc, char **argv, t_stack *a, bool *verbose);
static bool	has_dupes(t_stack *a);

bool	get_args(int argc, char **argv, t_stack *stks[2], bool *verbose)
{
	if (!parse_args(argc, argv, stks[e_a], verbose) || has_dupes(stks[e_a]))
	{
		free_stacks(stks);
		stks = NULL;
		return (false);
	}
	return (true);
}

static void	parse_verbose(int *argc, char ***argv, t_stack *a, bool *verbose)
{
	const bool	has_flag_short = ft_strncmp((*argv)[1], "-v", 3) == 0;
	const bool	has_flag_long = ft_strncmp((*argv)[1], "--verbose", 10) == 0;

	(void)verbose;
	(void)argc;
	(void)argv;
	(void)a;
	if (PS_DEBUG && *argc > 1 && (has_flag_short || has_flag_long))
	{
		*verbose = true;
		(*argv)++;
		(*argc)--;
		a->cap--;
	}
}

static bool	write_args(char **usr_in, t_stack *a, int argc)
{
	size_t	i;

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

static bool	parse_args(int argc, char **argv, t_stack *a, bool *verbose)
{
	char	**usr_in;

	parse_verbose(&argc, &argv, a, verbose);
	if (argc == 2)
		usr_in = ft_split(argv[1], ' ');
	else
		usr_in = (argv + 1);
	if (!usr_in)
		return (false);
	if (argc == 2 && !usr_in[0])
	{
		freecharr(usr_in);
		return (false);
	}
	return (write_args(usr_in, a, argc));
}

static bool	has_dupes(t_stack *a)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < a->size)
	{
		j = i + 1;
		while (j < a->size)
		{
			if (a->data[from_head(*a, -i)] == a->data[from_head(*a, -j)])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}
