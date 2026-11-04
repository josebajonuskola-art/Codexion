/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_util_funcs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:59:27 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/04 11:59:45 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

int sim_is_finished(t_simulation *sim)
{
	int is_finished;

	is_finished = 0;
	pthread_mutex_lock(&sim->simulation_mutex);
	if (sim->is_finished == 1)
		is_finished = 1;
	pthread_mutex_unlock(&sim->simulation_mutex);
	return (is_finished);
}
