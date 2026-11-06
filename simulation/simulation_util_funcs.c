/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_util_funcs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:59:27 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 16:10:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function calculates and returns the time when the next dongle
// used by the specified coder will become available, by comparing the
// cooldown expiration times of both the left and right dongles.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder whose dongles are
// being checked.
long long	get_smaller_time(t_simulation *sim, t_coder *coder)
{
	long long	actual_time;
	long long	right_dongles_time;
	long long	left_dongles_time;

	actual_time = get_time_ms();
	right_dongles_time = sim->config->dongle_cooldown
		- (actual_time - coder->right_dongle->cooldown_starting_time)
		+ actual_time;
	left_dongles_time = sim->config->dongle_cooldown
		- (actual_time - coder->left_dongle->cooldown_starting_time)
		+ actual_time;
	if (right_dongles_time > left_dongles_time)
		return (right_dongles_time);
	else
		return (left_dongles_time);
}

// This function retrieves the current system time in milliseconds using
// gettimeofday. It serves as the reference clock for all time calculations
// within the simulation.
long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

// This function checks whether the simulation has finished in a thread-safe
// manner by locking the simulation mutex before reading the 'is_finished' flag.
//
// The 'sim' parameter is a pointer to the simulation structure containing
// the mutex and the termination flag.
int	sim_is_finished(t_simulation *sim)
{
	int	is_finished;

	is_finished = 0;
	pthread_mutex_lock(&sim->simulation_mutex);
	if (sim->is_finished == 1)
		is_finished = 1;
	pthread_mutex_unlock(&sim->simulation_mutex);
	return (is_finished);
}
