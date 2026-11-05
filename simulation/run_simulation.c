/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 11:13:03 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/24 10:24:28 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function creates the monitor and coder threads, then waits
// for all of them to finish by joining them.
//
// The 'simulation' pointer references the simulation structure
// used to create and manage the threads.
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
		{
			//printf("Mini error\n");
			return (1);
		}
		//printf("Termina el coder %d\n", i);
		i++;

	}
	simulation->heap_sorter = malloc(sizeof(t_heap_sorter));
	if (!simulation->heap_sorter)
		return (free(simulation), 1);
	//printf("Before initing heap_thread\n");
	if (pthread_create(&simulation->heap_sorter->heap_sorter_thread, NULL,
					   init_heap_thread, simulation) != 0)
		return (1);
/* 	while (i--)
		pthread_join(simulation->coders[i].coder_thread, NULL);
	pthread_join(simulation->monitor->monitor_thread, NULL); */

	return (0);
}

void	join_threads(t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_join(sim->coders[i].coder_thread, NULL);
		i++;
	}
	pthread_join(sim->monitor->monitor_thread, NULL);
	pthread_join(sim->heap_sorter->heap_sorter_thread, NULL);
}
// This function starts and runs the simulation, ensuring that the
// required threads are created successfully.
//
// The 'simulation' pointer references the simulation structure
// used to create and manage the threads.
int	run_simulation(t_simulation *simulation)
{
	if (init_threads(simulation) == 1)
		return (1);
	join_threads(simulation);
	return (0);
}
