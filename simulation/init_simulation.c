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
void	init_mutex_destroy(int selector, int i, t_simulation *sim)
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
	else
		pthread_mutex_destroy(&sim->simulation_mutex);
}

// This function initializes all coders in the simulation.
//
// The 'sim' pointer references the simulation structure whose
// coder fields are initialized.
int	init_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		sim->coders[i].n_coder = i + 1;
		sim->coders[i].n_compiles_done = 0;
		sim->coders[i].last_compile = get_time_ms();
		sim->coders[i].actual_step = 0;
		sim->coders[i].can_process = 0;
		sim->coders[i].right_dongle = &sim->dongles[i];
		sim->coders[i].sim = sim;
		if (sim->config->number_of_coders == 1)
			sim->coders[i].left_dongle = &sim->dongles[i + 1];
		else if (i == sim->config->number_of_coders - 1)
			sim->coders[i].left_dongle = &sim->dongles[0];
		else
			sim->coders[i].left_dongle = &sim->dongles[i + 1];
		if (pthread_mutex_init(&sim->coders[i].coder_mutex, NULL) != 0)
		{
			init_mutex_destroy(0, i, sim);
			return (1);
		}
		i++;
	}
	return (0);
}

// This function initializes all dongles in the simulation.
//
// The 'sim' pointer references the simulation structure whose
// dongle fields are initialized.
int	init_dongles(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		sim->dongles[i].n_dongle = i;
		sim->dongles[i].is_connected = 0;
		sim->dongles[i].is_chilled = 0;
		sim->dongles[i].cooldown_starting_time = 0;
		sim->dongles[i].user = NULL;
		if (pthread_mutex_init(&sim->dongles[i].dongle_mutex, NULL) != 0)
		{
			init_mutex_destroy(1, i, sim);
			return (1);
		}
		//maybe the 'i' has to be 1 at the beggining instead of 0 to return the
		//correct amount of free
		i++;
	}
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

	//Mallocs of available coders and not available coders arent done
	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	sim->config = config;
	sim->is_finished = 0;
	sim->n_available_coders = 0;
	sim->n_not_available_coders = 0;
	sim->available_coders = malloc(sizeof(t_request) * config->number_of_coders);
	sim->not_available_coders = malloc(sizeof(t_request) * config->number_of_coders);
	sim->dongles = malloc(sizeof(t_dongle) * config->number_of_coders);
	if (!sim->dongles)
		return (free(sim), NULL);
	sim->coders = malloc(sizeof(t_coder) * config->number_of_coders);
	if (!sim->coders)
		return (free(sim->dongles), free(sim), NULL);
	if (pthread_mutex_init(&sim->simulation_mutex, NULL) != 0)
	{
		init_mutex_destroy(0, 3, sim);
		return (free(sim->dongles), free(sim->coders), NULL);
	}
	if (init_dongles(sim) != 0)
		return (free(sim->coders), free(sim->dongles), free(sim), NULL);
	if (init_coders(sim) != 0)
		return (free(sim->coders), free(sim->dongles), free(sim), NULL);
	if (init_heap(sim) != 0)
		return (free(sim->coders), free(sim->dongles),
			free(sim->heap), free(sim), NULL);
	sim->start_time = get_time_ms();
	return (sim);
}
