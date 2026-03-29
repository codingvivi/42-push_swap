/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:04:31 by lrain             #+#    #+#             */
/*   Updated: 2026/03/30 17:17:48 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_stack_idx
{
	e_a,
	e_b,
}		t_stack_idx;

typedef struct s_stack
{
	int	*data;
	int	head;
	int	tail;
}		t_stack;
