/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickop.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:22:19 by lrain             #+#    #+#             */
/*   Updated: 2026/04/09 19:24:28 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PICKOP_H
# define PICKOP_H

# include "stacks.h"
# include <sys/types.h>

typedef void	(*t_op)(t_stack *[2]);

t_op			pick_b(ssize_t n);

t_op			pick_a(ssize_t n);

t_op			pick_both(ssize_t n);

#endif
