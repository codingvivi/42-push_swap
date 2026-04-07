/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_ops.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 22:59:32 by lrain             #+#    #+#             */
/*   Updated: 2026/04/08 00:33:06 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"
#include <stdbool.h>
#include <sys/types.h>

ssize_t	**generate_costs(const t_stack stks[2], bool verbose);
