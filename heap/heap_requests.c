/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_requests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:36:48 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/29 19:53:45 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	coder_request(t_simulation *sim, t_coder *coder)
{
	t_request	request;
	long long	actual_time;

	actual_time = get_time_ms();
	pthread_mutex_lock(&sim->heap->heap_mutex);
	request.coder = coder;
	request.arrival_number = sim->arrival_counter;
	sim->arrival_counter++;
	request.time_remaining = actual_time - sim->coders->last_compile;
	pthread_mutex_unlock(&sim->heap->heap_mutex);
	heap_adder(sim, request);

}

void	heap_adder(t_simulation *sim, t_request request)
{
	if (sim->config->scheduler == FIFO)
		heap_add_fifo(sim, request);

	else
		printf("hello\n");
// all the 'edf' stuff;
}
