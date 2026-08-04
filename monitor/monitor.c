/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:02:55 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/24 19:16:55 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function runs the monitor thread. The monitor checks whether
// any coder has burned out and stops the simulation if that happens.
//
// The 'value' parameter is a pointer to the simulation structure.
void	*init_monitoring(void *value)
{

	int i;
	i = 2;
	/*
	int		compiles;
	long long actual_time;
	t_simulation *sim;

	i = 1;
	compiles = 0;
	sim = (t_simulation *)value;

	while(sim->is_finished != 1)
	{
		usleep(10000);
		i = 0;
		while(i < sim->config->number_of_coders)
		{
			actual_time = get_time_ms();
			if (compiles == sim->config->number_of_coders)
				sim->is_finished = 1;
			if(sim->coders[i].n_compiles_done == sim->config->number_of_compiles_requiered)
				compiles++;
			if(actual_time - sim->coders[i].time_in_process >= sim->config->time_to_burnout)
			{
				printf("a coder has been burnout\n");
				sim->is_finished = 1;
			}
			i++;
		}
	}*/
	while(i != 0)
		i++;
	return(value);
}

