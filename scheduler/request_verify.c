/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_verify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:47:13 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/30 13:07:16 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	request_verify(t_simulation *sim, t_coder *coder)
{
	pthread_mutex_lock(&sim->heap->heap_mutex);
	while((is_heap_top(sim, coder) != 1) || (usable_dongle(sim, coder->right_dongle) != 1) || (usable_dongle(sim, coder->left_dongle) != 1))
		pthread_cond_wait(&sim->heap->heap_cond,&sim->heap->heap_mutex);
	pthread_mutex_unlock(&sim->heap->heap_mutex);
}
