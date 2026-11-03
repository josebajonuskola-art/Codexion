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

void	wake_up_coders(t_simulation *sim)
{
	pthread_mutex_lock(&sim->heap->heap_mutex);
	pthread_cond_broadcast(&sim->heap->heap_cond);
	pthread_mutex_unlock(&sim->heap->heap_mutex);
}

int	check_burnout(t_simulation *sim, int coder)
{
	long long	actual_time;

	actual_time = get_time_ms();
	if (actual_time - sim->coders[coder].last_compile
		>= sim->config->time_to_burnout)
	{
		pthread_mutex_lock(&sim->print_mutex);
		printf("%lld %d burned out\n",
			actual_time - sim->start_time, coder + 1);
		pthread_mutex_unlock(&sim->print_mutex);
		return (1);
	}
	return (0);
}

int	check_compiles_done(t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		if (sim->coders[i].n_compiles_done
			< sim->config->number_of_compiles_requiered)
			return (0);
		i++;
	}
	return (1);
}

// This function runs the monitor thread. The monitor checks whether
// any coder has burned out and stops the simulation if that happens.
//
// The 'value' parameter is a pointer to the simulation structure.
void	*init_monitoring(void *value)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)value;
	while (sim->is_finished != 1)
	{
		usleep(1000);
		i = 0;
		pthread_mutex_lock(&sim->simulation_mutex);
		while (i < sim->config->number_of_coders)
		{
			if (check_burnout(sim, i) == 1  || check_compiles_done(sim) == 1 )
			{
				sim->is_finished = 1;
				//printf("The simulation is finished\n");
				pthread_mutex_unlock(&sim->simulation_mutex);
				//break ;
				return (NULL);
			}
			i++;
		}
		pthread_mutex_unlock(&sim->simulation_mutex);
	}
	//printf("fuera del bucle\n");
	wake_up_coders(sim);
	return (NULL);
}
