/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 17:55:03 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 17:45:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function executes the complete processing sequence for a coder, which
// consists of compiling, checking completion status, debugging, and refactoring.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder executing the process.
int	coder_process(t_simulation *sim, t_coder *coder)
{
	if (start_to_compile(sim, coder) == 1)
		return (1);
	if (coder->n_compiles_done == sim->config->number_of_compiles_requiered)
		return (1);
	if (start_to_debug(sim, coder) == 1)
		return (1);
	if (start_to_refactor(sim, coder) == 1)
		return (1);
	return (0);
}

// This function simulates the compilation phase of a coder. It updates the
// compile timestamp, logs state changes, waits for the compilation duration,
// releases both acquired dongles with updated cooldown start times, increments
// the compile count, and signals the condition variable to wake waiting threads.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder starting compilation.
int	start_to_compile(t_simulation *sim, t_coder *coder)
{
	if (sim_is_finished(sim) == 1)
		return (1);
	pthread_mutex_lock(&coder->coder_mutex);
	coder->last_compile = get_time_ms();
	pthread_mutex_unlock(&coder->coder_mutex);
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
	pthread_mutex_lock(&coder->coder_mutex);
	coder->actual_step = 1;
	coder->n_compiles_done += 1;
	pthread_mutex_unlock(&coder->coder_mutex);
	pthread_mutex_lock(&sim->heap->heap_mutex);
	pthread_cond_broadcast(&sim->heap->heap_cond);
	pthread_mutex_unlock(&sim->heap->heap_mutex);
	return (0);
}

// This function simulates the debugging phase of a coder. It logs the state,
// waits for the configured debug time, and updates the coder's current step.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder debugging.
int	start_to_debug(t_simulation *sim, t_coder *coder)
{
	if (sim_is_finished(sim) == 1)
		return (1);
	print_process(sim, coder, 1);
	usleep(sim->config->time_to_debug * 1000);
	pthread_mutex_lock(&coder->coder_mutex);
	coder->actual_step = 2;
	pthread_mutex_unlock(&coder->coder_mutex);
	return (0);
}

// This function simulates the refactoring phase of a coder. It logs the state,
// waits for the refactoring duration, updates the coder's step, and if the
// compilation target has not been reached, constructs and pushes a new request
// into the heap.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder refactoring.
int	start_to_refactor(t_simulation *sim, t_coder *coder)
{
	t_request	last_request;
	t_coder		*actual_coder;

	actual_coder = coder;
	if (sim_is_finished(sim) == 1)
		return (1);
	print_process(sim, coder, 2);
	usleep(sim->config->time_to_refactor * 1000);
	pthread_mutex_lock(&coder->coder_mutex);
	coder->actual_step = 0;
	pthread_mutex_unlock(&coder->coder_mutex);
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
