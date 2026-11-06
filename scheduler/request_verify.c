/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_verify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:47:13 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 16:30:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function blocks the calling coder thread using a condition variable
// until the heap sorter/dispatcher grants permission to process its request
// (can_process != 0) or until the simulation is marked as finished.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder waiting for verification.
void	request_verify(t_simulation *sim, t_coder *coder)
{
	pthread_mutex_lock(&sim->heap->heap_mutex);
	while (coder->can_process == 0 && sim_is_finished(sim) == 0)
		pthread_cond_wait(&sim->heap->heap_cond, &sim->heap->heap_mutex);
	coder->can_process = 0;
	pthread_mutex_unlock(&sim->heap->heap_mutex);
}
