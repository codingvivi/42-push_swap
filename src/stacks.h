/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:04:31 by lrain             #+#    #+#             */
/*   Updated: 2026/04/07 22:28:58 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include <stddef.h>
# include <sys/types.h>
typedef enum e_stack_idx
{
	e_a,
	e_b,
}			t_stack_idx;
typedef enum e_move_idx
{
	e_top_b,
	e_dest_a,
}			t_move_idx;

typedef struct s_stack
{
	int		*data;
	size_t	head;
	size_t	size;
	size_t	cap;
}			t_stack;

typedef struct s_subseq
{
	int		*seq;
	size_t	size;
}			t_subseq;
#endif
