/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_idx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:31:36 by lrain             #+#    #+#             */
/*   Updated: 2026/03/31 19:55:18 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_IDX_H
# define GET_IDX_H

# include "stacks.h"
# include <stddef.h>
# include <sys/types.h>

ssize_t	get_idx(size_t origin, int motion, size_t cap);
ssize_t	from_head(t_stack s, int motion);

#endif
