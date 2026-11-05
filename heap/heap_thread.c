/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:58:40 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/05 22:55:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	*init_heap_thread(void *value)
{
	t_simulation	*sim;
	t_request		actual_coder;

	sim = (t_simulation *)value;
	while (sim_is_finished(sim) != 1)
	{
		usleep(500);
		pthread_mutex_lock(&sim->heap->heap_mutex);
		while (sim->heap->size > 0)
		{
			actual_coder = heap_pop(sim);
			available_or_not_scheduler(sim, actual_coder);
		}
		coder_runner_and_schedule_reseter(sim);
		pthread_cond_broadcast(&sim->heap->heap_cond);
		pthread_mutex_unlock(&sim->heap->heap_mutex);
		if (sim_is_finished(sim) == 1)
			break ;
	}
	return (NULL);
}

void	available_or_not_scheduler(t_simulation *sim, t_request coder_request)
{
	t_coder	*actual_coder;

	actual_coder = coder_request.coder;
	if (usable_dongles(sim, actual_coder) == 1
		&& actual_coder->n_compiles_done <= sim->config->number_of_compiles_requiered)
	{
		use_dongles(actual_coder);
		sim->avl_coders[sim->n_avl_coders] = coder_request;
		sim->n_avl_coders++;
	}
	else
	{
		sim->not_avl_coders[sim->n_not_avl_coders] = coder_request;
		sim->n_not_avl_coders++;
	}
}

void	coder_runner_and_schedule_reseter(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->simulation_mutex);
	while (i < sim->n_avl_coders)
		sim->avl_coders[i++].coder->can_process = 1;
	i = 0;
	while (i < sim->n_not_avl_coders)
		heap_push(sim, sim->not_avl_coders[i++]);
	sim->n_avl_coders = 0;
	sim->n_not_avl_coders = 0;
	pthread_mutex_unlock(&sim->simulation_mutex);
}
