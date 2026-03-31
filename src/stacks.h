/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:04:31 by lrain             #+#    #+#             */
/*   Updated: 2026/03/31 18:43:57 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include <stddef.h>
typedef enum e_stack_idx
{
	e_a,
	e_b,
}			t_stack_idx;

typedef struct s_stack
{
	int		*data;
	size_t	head;
	size_t	size;
	size_t	cap;
}			t_stack;

#endif
