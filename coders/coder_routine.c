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

// Ive moved the heap pop from start_to_refactor to start_to_compile

int	start_to_compile(t_simulation *sim, t_coder *coder)
{
	if (sim->is_finished == 1)
		return (1);
	coder->last_compile = get_time_ms();
	print_process(sim, coder, 0);
	usleep(sim->config->time_to_compile * 1000);
	pthread_mutex_lock(&coder->right_dongle->dongle_mutex);
	coder->right_dongle->is_connected = 0;
	coder->right_dongle->cooldown_starting_time = get_time_ms();
	pthread_mutex_unlock(&coder->right_dongle->dongle_mutex);
	pthread_mutex_lock(&coder->left_dongle->dongle_mutex);
	coder->left_dongle->is_connected = 0;
	coder->left_dongle->cooldown_starting_time = get_time_ms();
	pthread_mutex_unlock(&coder->left_dongle->dongle_mutex);
	coder->actual_step = 1;
	coder->n_compiles_done += 1;
	pthread_mutex_lock(&sim->heap->heap_mutex);
	pthread_cond_broadcast(&sim->heap->heap_cond);
	pthread_mutex_unlock(&sim->heap->heap_mutex);
	
	return (0);
}

int	start_to_debug(t_simulation *sim, t_coder *coder)
{
	if (sim->is_finished == 1)
		return (1);
	print_process(sim, coder, 1);
	usleep(sim->config->time_to_debug * 1000);
	coder->actual_step = 2;
	return (0);
}

int	start_to_refactor(t_simulation *sim, t_coder *coder)
{
	t_request	last_request;
	t_coder *actual_coder;

	actual_coder = coder;
	if (sim->is_finished == 1)
		return (1);
	print_process(sim, coder, 2);
	usleep(sim->config->time_to_refactor * 1000);
	coder->actual_step = 0;
	last_request.coder = actual_coder;
	pthread_mutex_lock(&sim->simulation_mutex);
	last_request.arrival_number = sim->arrival_counter;
	last_request.time_remaining = coder->last_compile
		+ sim->config->time_to_burnout;
	sim->arrival_counter++;
	pthread_mutex_unlock(&sim->simulation_mutex);
	pthread_mutex_lock(&sim->heap->heap_mutex);
	if (coder->n_compiles_done < sim->config->number_of_compiles_requiered)
		heap_push(sim, last_request);
	pthread_mutex_unlock(&sim->heap->heap_mutex);
	return (0);
}

int	coder_process(t_simulation *sim, t_coder *coder)
{
	pthread_mutex_lock(&coder->coder_mutex);
	if (start_to_compile(sim, coder) == 1)
		return (pthread_mutex_unlock(&coder->coder_mutex), 1);
	if (coder->n_compiles_done == sim->config->number_of_compiles_requiered)
		return (pthread_mutex_unlock(&coder->coder_mutex), 1);
	if (start_to_debug(sim, coder) == 1)
		return (pthread_mutex_unlock(&coder->coder_mutex), 1);
	if (start_to_refactor(sim, coder) == 1)
		return (pthread_mutex_unlock(&coder->coder_mutex), 1);
	pthread_mutex_unlock(&coder->coder_mutex);
	return (0);
}
