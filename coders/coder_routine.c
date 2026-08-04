/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 17:55:03 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/30 13:29:11 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// Still need to verify how the 'time to burnout' works. I'll have to implement
// it in the monitoring.


int	start_to_compile(t_simulation *sim, t_coder *coder)
{
	printf("coder-> has start compiling\n");
	pthread_mutex_lock(&coder->right_dongle->dongle_mutex);
	pthread_mutex_lock(&coder->left_dongle->dongle_mutex);
	use_dongles(coder);
	//else
	//	return (pthread_mutex_unlock(coder->right_dongle->dongle_mutex), 1);

	usleep(sim->config->time_to_compile);
	coder->right_dongle->is_connected = 0;
	coder->right_dongle->cooldown_starting_time = get_time_ms();
	coder->left_dongle->is_connected = 0;
	coder->left_dongle->cooldown_starting_time = get_time_ms();
	coder->actual_step = 1;
	coder->time_in_process = get_time_ms();
	//pthread_mutex_unlock(&sim->coders[coder->n_coder].coder_mutex);
	pthread_mutex_unlock(&coder->right_dongle->dongle_mutex);
	pthread_mutex_unlock(&coder->left_dongle->dongle_mutex);
	printf("coder-> has end compiling\n");
	return(0);
}

int	start_to_debug(t_simulation *sim, t_coder *coder)
{
	printf("coder->  has start debuging\n");
	pthread_mutex_lock(&sim->dongles->dongle_mutex);
	if(coder->right_dongle->is_connected == 0 &&
		coder->left_dongle->is_connected == 0)
			usleep(sim->config->time_to_debug);
	else
		return (pthread_mutex_unlock(&sim->dongles->dongle_mutex), 1);
	coder->actual_step = 2;
	pthread_mutex_unlock(&sim->dongles->dongle_mutex);
	printf("coder-> has end debuging\n");
	return(0);
}

int	start_to_refactor(t_simulation *sim, t_coder *coder)
{
	printf("coder-> has start refactoring\n");
	usleep(sim->config->time_to_refactor);
	coder->n_compiles_done += 1;
	coder->actual_step = 0;
	pthread_mutex_lock(&sim->heap->heap_mutex);
	sim->heap->requests->arrival_number = sim->arrival_counter++;
	heap_push(sim, heap_pop(sim));
	print_heap(sim->heap);
	pthread_cond_broadcast(&sim->heap->heap_cond);
	pthread_mutex_unlock(&sim->heap->heap_mutex);
	//pthread_mutex_unlock(&sim->coders[coder->n_coder].coder_mutex);
	printf("coder-> has end refactoring\n");
	return(0);
}

int	coder_process(t_simulation *sim, t_coder *coder)
{
	long long	pre_procces_time;
	long long	procces_finish_time;

	pthread_mutex_lock(&coder->coder_mutex);
	printf("Thread coder %d\n", coder->n_coder);
	pre_procces_time = get_time_ms();
	start_to_compile(sim, coder);
	start_to_debug(sim, coder);
	start_to_refactor(sim, coder);
	procces_finish_time = get_time_ms();
	coder->time_in_process = procces_finish_time - pre_procces_time;
	pthread_mutex_unlock(&coder->coder_mutex);
	return(0);
}
