/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_requests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:36:48 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 17:20:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function creates a new compilation request for the specified coder,
// assigns the current arrival order index, calculates its burnout deadline,
// and appends the request to the heap in a thread-safe manner using heap_mutex.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder issuing the request.
void	coder_request(t_simulation *sim, t_coder *coder)
{
	t_request	request;
	long long	actual_time;

	actual_time = get_time_ms();
	pthread_mutex_lock(&sim->heap->heap_mutex);
	request.coder = coder;
	request.arrival_number = sim->arrival_counter;
	sim->arrival_counter++;
	request.time_remaining = actual_time + sim->config->time_to_burnout;
	sim->heap->requests[sim->heap->size] = request;
	sim->heap->size++;
	pthread_mutex_unlock(&sim->heap->heap_mutex);
}
