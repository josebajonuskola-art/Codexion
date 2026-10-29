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
	printf("inside the func\n");
	if (usable_dongles(sim, actual_coder) == 1)
	{
		use_dongles(actual_coder);
		sim->available_coders[sim->n_available_coders] = coder_request;
		printf("The coder %d has been added to available coders\n", sim->available_coders[sim->n_available_coders].coder->n_coder);
		sim->n_available_coders++;

	}
	else
	{
		sim->not_available_coders[sim->n_not_available_coders] = coder_request;
		printf("The coder %d has been added to not available coders\n", sim->not_available_coders[sim->n_not_available_coders].coder->n_coder);
		sim->n_not_available_coders++;

	}

}
/*
void	coder_runner_and_schedule_reseter(t_simulation *sim)
{
	int i;
	t_request actual_request;

	// I've to clean the arrays after using them
	i = 0;
	while (sim->available_coders[i])
	{
		if (!sim->available_coders[i])
			break ;
		sim->available_coders[i].can_process = 1;
		sim->available_coders[i] = NULL;
		i++;
	}
	i = 0;
	while (sim->not_available_coders[i])
	{
		if (!&sim->not_available_coders[i])
			break ;
		actual_request.arrival_number = i;
		actual_request.coder = &sim->not_available_coders[i];
		actual_request.time_remaining = get_time_ms();
		heap_push(sim, actual_request);
		sim->not_available_coders[i] = NULL;
		i++;
	}
}*/

void	*init_heap_thread(void *value)
{
	t_simulation	*sim;
	t_request actual_coder;

	//printf("Before the heap while loop\n");
	sim = (t_simulation *)value;
	while (sim->is_finished != 1)
	{
		//printf("After the heap while loop\n");
		usleep(1000);
		pthread_mutex_lock(&sim->heap->heap_mutex);
		while (sim->heap->size > 0)
		{
			printf("Inside the heap sorter\n");

			//printf("tercer loop debug1\n");
			actual_coder = heap_pop(sim);
			//printf("tercer loop debug2\n");

			pthread_mutex_unlock(&sim->heap->heap_mutex);
			//printf("tercer loop debug3\n");

			//pthread_mutex_lock(&sim->dongles->dongle_mutex);
			//printf("tercer loop debug4\n");

			available_or_not_scheduler(sim, actual_coder);
			//printf("tercer loop debug5\n");

			pthread_mutex_unlock(&sim->dongles->dongle_mutex);
			//printf("tercer loop debug6\n");
		}
		sim->n_available_coders = 0;
		sim->n_not_available_coders = 0;
		printf("First available coder: %d\n", sim->available_coders[0].coder->n_coder);
		printf("First not available coder: %d\n", sim->not_available_coders[0].coder->n_coder);
		// coder_runner_and_schedule_reseter(sim);
	}
	return (value);
}
