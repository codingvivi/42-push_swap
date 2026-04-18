/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_ops.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 22:59:32 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 18:51:56 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COST_OPS_H
# define COST_OPS_H

# include "stacks.h"
# include <stdbool.h>
# include <sys/types.h>

ssize_t	get_rotate_cost(size_t tgt_idx, size_t size);
ssize_t	**generate_costs(t_stack *stks[2], bool verbose);

#endif
