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
	if(pthread_create(&simulation->monitor->monitor_thread, NULL,
		init_monitoring, simulation) != 0)
	//here i may have to destroy the broken thread
		return(1);
	while (i < simulation->config->number_of_coders)
	{
		if(pthread_create(&simulation->coders[i].coder_thread, NULL,
			init_coders_threads, &simulation->coders[i]) != 0)
			return(1);
		i++;
	}
	pthread_join(simulation->monitor->monitor_thread, NULL);
	while(i--)
		pthread_join(simulation->coders[i].coder_thread, NULL);
	return(0);
}

// This function starts and runs the simulation, ensuring that the
// required threads are created successfully.
//
// The 'simulation' pointer references the simulation structure
// used to create and manage the threads.
int	run_simulation(t_simulation *simulation)
{
	init_threads(simulation);
	// if(init_threads(simulation) == 1)

	//	return(1);
	//else
	//	return(0);
	return(0);
}
