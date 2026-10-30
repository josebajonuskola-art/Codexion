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
	//pthread_mutex_lock(&sim->heap->heap_mutex);
	coder->last_compile = get_time_ms();
	//heap_pop(sim);
	//use_dongles(coder);
	print_take_dongles(sim, coder);
	printf("%lld %d is compiling\n",
		get_time_ms() - sim->start_time, coder->n_coder);
	//pthread_mutex_unlock(&sim->heap->heap_mutex);
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
	pthread_cond_broadcast(&sim->heap->heap_cond);
	return (0);
}

int	start_to_debug(t_simulation *sim, t_coder *coder)
{
	if (sim->is_finished == 1)
		return (1);
	printf("%lld %d is debugging\n",
		get_time_ms() - sim->start_time, coder->n_coder);
	usleep(sim->config->time_to_debug * 1000);
	coder->actual_step = 2;
	//pthread_mutex_unlock(&sim->dongles->dongle_mutex);
	return (0);
}

int	start_to_refactor(t_simulation *sim, t_coder *coder)
{
	t_request	last_request;
	t_coder *actual_coder;

	actual_coder = coder;
	if (sim->is_finished == 1)
		return (1);
	printf("%lld %d is refactoring\n",
		get_time_ms() - sim->start_time, coder->n_coder);
	usleep(sim->config->time_to_refactor * 1000);
	coder->actual_step = 0;
	last_request.coder = actual_coder;
	last_request.arrival_number = sim->arrival_counter;
	sim->arrival_counter++;
	printf("Before heap_push if condition\n");
	if (coder->n_compiles_done < sim->config->number_of_compiles_requiered)
	{
		pthread_mutex_lock(&sim->heap->heap_mutex);
		printf("Ready to heap_push\n");
		heap_push(sim, last_request);
		print_heap(sim->heap);
	}
	pthread_mutex_unlock(&sim->heap->heap_mutex);
	return (0);
}

int	coder_process(t_simulation *sim, t_coder *coder)
{
	if (coder->n_compiles_done == sim->config->number_of_compiles_requiered)
		return (1);
	pthread_mutex_lock(&coder->coder_mutex);
	if (start_to_compile(sim, coder) == 1)
		return (1);
	if (start_to_debug(sim, coder) == 1)
		return (1);
	if (start_to_refactor(sim, coder) == 1)
		return (1);
	coder->can_process = 0;
	pthread_mutex_unlock(&coder->coder_mutex);
	//print_heap(sim->heap);
	// printf("El coder ha terminado su proceso\n");
	return (0);
}
