/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 00:39:17 by lrain             #+#    #+#             */
/*   Updated: 2026/04/03 22:52:28 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "stacks.h"
# include <stdbool.h>
# include <stddef.h>

t_stack	init_stack(size_t cap);
bool	init_ab(size_t stk_size, t_stack stks[2]);
bool	init_a(int argc, char **argv, t_stack *a, bool *verbose);

#endif
