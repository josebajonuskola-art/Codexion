/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_util_funcs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:59:27 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/05 23:45:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

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

long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

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
