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
	while (coder->can_process == 0 && sim_is_finished(sim) == 0)
		pthread_cond_wait(&sim->heap->heap_cond, &sim->heap->heap_mutex);
	pthread_mutex_lock(&coder->coder_mutex);
	coder->can_process = 0;
	pthread_mutex_unlock(&coder->coder_mutex);
	pthread_mutex_unlock(&sim->heap->heap_mutex);
}

