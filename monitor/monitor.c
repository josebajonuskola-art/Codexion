/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:02:55 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 16:45:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function runs the monitor thread. The monitor checks whether
// any coder has burned out and stops the simulation if that happens.
//
// The 'value' parameter is a pointer to the simulation structure.
void	*init_monitoring(void *value)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)value;
	while (sim_is_finished(sim) != 1)
	{
		usleep(1000);
		i = 0;
		while (i < sim->config->number_of_coders)
		{
			if (check_burnout(sim, i) == 1 || check_compiles_done(sim) == 1)
			{
				pthread_mutex_lock(&sim->simulation_mutex);
				sim->is_finished = 1;
				pthread_mutex_unlock(&sim->simulation_mutex);
				return (NULL);
			}
			i++;
		}
	}
	wake_up_coders(sim);
	return (NULL);
}

// This function broadcasts a signal to the condition variable of the heap
// to wake up any coder threads that might be waiting.
//
// The 'sim' parameter is a pointer to the main simulation structure.
void	wake_up_coders(t_simulation *sim)
{
	pthread_mutex_lock(&sim->heap->heap_mutex);
	pthread_cond_broadcast(&sim->heap->heap_cond);
	pthread_mutex_unlock(&sim->heap->heap_mutex);
}

// This function checks whether a specific coder has exceeded the burnout limit.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is the index of the coder to check.
int	check_burnout(t_simulation *sim, int coder)
{
	long long	actual_time;

	actual_time = get_time_ms();
	pthread_mutex_lock(&sim->coders[coder].coder_mutex);
	if (actual_time - sim->coders[coder].last_compile
		>= sim->config->time_to_burnout)
	{
		pthread_mutex_unlock(&sim->coders[coder].coder_mutex);
		pthread_mutex_lock(&sim->print_mutex);
		printf("%lld %d burned out\n",
			actual_time - sim->start_time, coder + 1);
		pthread_mutex_unlock(&sim->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&sim->coders[coder].coder_mutex);
	return (0);
}

// This function checks if all coders have completed the required
// number of compiles.
//
// The 'sim' parameter is a pointer to the main simulation structure.
int	check_compiles_done(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i].coder_mutex);
		if (sim->coders[i].n_compiles_done
			< sim->config->number_of_compiles_requiered)
		{
			pthread_mutex_unlock(&sim->coders[i].coder_mutex);
			return (0);
		}
		pthread_mutex_unlock(&sim->coders[i].coder_mutex);
		i++;
	}
	return (1);
}
