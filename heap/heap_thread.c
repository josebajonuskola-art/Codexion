/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:58:40 by juskola-          #+#    #+#             */
/*   Updated: 2026/10/28 17:59:21 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	available_or_not_scheduler(t_simulation *sim, t_request coder_request)
{
	t_coder *actual_coder;

	actual_coder = coder_request.coder;
	if (usable_dongles(sim, actual_coder) == 1)
	{
		use_dongles(actual_coder);
		sim->available_coders[sim->n_available_coders] = coder_request;
		printf("The coder %d has been added to available coders\n",
			sim->available_coders[sim->n_available_coders].coder->n_coder);
		sim->n_available_coders++;

	}
	else
	{
		sim->not_available_coders[sim->n_not_available_coders] = coder_request;
		printf("The coder %d has been added to not available coders\n",
			sim->not_available_coders[sim->n_not_available_coders].coder->n_coder);
		sim->n_not_available_coders++;
	}

}

void	coder_runner_and_schedule_reseter(t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->n_available_coders)
		sim->available_coders[i++].coder->can_process = 1;
	i = 0;
	while (i < sim->n_not_available_coders)
		heap_push(sim, sim->not_available_coders[i++]);
}

void	*init_heap_thread(void *value)
{
	t_simulation	*sim;
	t_request actual_coder;
	int i;

	sim = (t_simulation *)value;
	i = 3;
	//while (sim->is_finished != 1)
	while(i--)
	{
		usleep(1000);
		pthread_mutex_lock(&sim->heap->heap_mutex);
		while (sim->heap->size > 0)
		{
			actual_coder = heap_pop(sim);
			pthread_mutex_unlock(&sim->heap->heap_mutex);
			available_or_not_scheduler(sim, actual_coder);
			pthread_mutex_unlock(&sim->dongles->dongle_mutex);
		}
		coder_runner_and_schedule_reseter(sim);
		sim->n_available_coders = 0;
		sim->n_not_available_coders = 0;
	}
	return (value);
}
