/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:40:21 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/28 17:35:50 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function destroys all previously initialized mutexes if an error
// occurs during the creation process.
//
// The 'selector' parameter determines whether coder or dongle mutexes
// should be destroyed. The 'i' parameter is used as a counter and indicates
// how many mutexes have been initialized. The 'sim' pointer references the
// simulation structure whose mutexes are being destroyed.
void	mtx_destroyer(int selector, int i, t_simulation *sim)
{
	if (selector == 0)
	{
		while (i--)
			pthread_mutex_destroy(&sim->coders[i].coder_mutex);
	}
	else if (selector == 1)
	{
		while (i--)
			pthread_mutex_destroy(&sim->dongles[i].dongle_mutex);
	}
	else if (selector == 2)
		pthread_mutex_destroy(&sim->heap->heap_mutex);
	else if (selector == 3)
		pthread_mutex_destroy(&sim->simulation_mutex);
	else
		pthread_mutex_destroy(&sim->print_mutex);
}

int	simulation_pattern_factory(t_simulation *sim, t_config *config)
{
	sim->config = config;
	sim->is_finished = 0;
	sim->n_avl_coders = 0;
	sim->n_not_avl_coders = 0;
	sim->start_time = get_time_ms();
	sim->avl_coders = malloc(sizeof(t_request) * config->number_of_coders);
	if (!sim->avl_coders)
		return (1);
	sim->not_avl_coders = malloc(sizeof(t_request) * config->number_of_coders);
	if (!sim->not_avl_coders)
		return (1);
	sim->dongles = malloc(sizeof(t_dongle) * config->number_of_coders);
	if (!sim->dongles)
		return (1);
	sim->coders = malloc(sizeof(t_coder) * config->number_of_coders);
	if (!sim->coders)
		return (1);
	return (0);
}

// This function creates the simulation receiving the early configuration.
// It also ensures all the memory is alloqued correctly. If any 'malloc'
// fails, de allocated memory is freed using 'free'.
//
// The 'config' pointer references to the parameters we receive in the
// program before running it up.
t_simulation	*sim_creator(t_config *config)
{
	t_simulation	*sim;

	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	if (simulation_pattern_factory(sim, config) == 1)
		return (garbage_collector(sim), NULL);
	if (pthread_mutex_init(&sim->simulation_mutex, NULL) != 0)
		return (mtx_destroyer(0, 3, sim), garbage_collector(sim), NULL);
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (mtx_destroyer(0, 4, sim), garbage_collector(sim), NULL);
	if (init_dongles(sim) != 0)
		return (garbage_collector(sim), NULL);
	if (init_coders(sim) != 0)
		return (garbage_collector(sim), NULL);
	if (init_heap(sim) != 0)
		return (garbage_collector(sim), NULL);
	return (sim);
}
