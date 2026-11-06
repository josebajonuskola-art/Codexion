/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 11:13:03 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 16:15:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function allocates memory for the monitor and heap sorter structures
// and creates the monitor, coder, and heap sorter threads required for the simulation.
//
// The 'simulation' parameter is a pointer to the main simulation structure.
long long	init_threads(t_simulation *simulation)
{
	int	i;

	i = 0;
	simulation->monitor = malloc(sizeof(t_monitor));
	if (pthread_create(&simulation->monitor->monitor_thread, NULL,
			init_monitoring, simulation) != 0)
		return (1);
	while (i < simulation->config->number_of_coders)
	{
		if (pthread_create(&simulation->coders[i].coder_thread, NULL,
				init_coders_threads, &simulation->coders[i]) != 0)
			return (1);
		i++;
	}
	simulation->heap_sorter = malloc(sizeof(t_heap_sorter));
	if (!simulation->heap_sorter)
		return (free(simulation), 1);
	if (pthread_create(&simulation->heap_sorter->heap_sorter_thread, NULL,
			init_heap_thread, simulation) != 0)
		return (1);
	return (0);
}

// This function starts the execution of the simulation by initializing all threads
// and waiting for their completion using join_threads.
//
// The 'simulation' parameter is a pointer to the main simulation structure.
int	run_simulation(t_simulation *simulation)
{
	if (init_threads(simulation) == 1)
		return (1);
	join_threads(simulation);
	return (0);
}

// This function waits for all active threads in the simulation to complete
// by calling pthread_join on each coder thread, the monitor thread, and the
// heap sorter thread.
//
// The 'sim' parameter is a pointer to the simulation structure containing thread IDs.
void	join_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_join(sim->coders[i].coder_thread, NULL);
		i++;
	}
	pthread_join(sim->monitor->monitor_thread, NULL);
	pthread_join(sim->heap_sorter->heap_sorter_thread, NULL);
}
