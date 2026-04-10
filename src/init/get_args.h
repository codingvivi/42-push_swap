/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/04/11 00:00:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_ARGS_H
# define GET_ARGS_H

# include "stacks.h"
# include <stdbool.h>

bool	get_args(int argc, char **argv, t_stack *stks[2], bool *verbose);

#endif
