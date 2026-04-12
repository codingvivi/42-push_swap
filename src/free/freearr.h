/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freearr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:35:57 by lrain             #+#    #+#             */
/*   Updated: 2026/04/10 19:40:06 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

typedef void	(*t_free_membr_fn)(void *args);

void			freearr(void **arr, size_t len, t_free_membr_fn freefn);
