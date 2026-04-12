/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestacks.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:23:28 by lrain             #+#    #+#             */
/*   Updated: 2026/04/10 20:23:28 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREESTACKS_H
# define FREESTACKS_H

# include "stacks.h"

void	free_stack(t_stack *sp);
void	free_stacks(t_stack *stks[2]);

#endif
