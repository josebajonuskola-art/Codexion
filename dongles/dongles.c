/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:58:14 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/27 20:16:37 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	usable_dongles(t_simulation *sim, t_coder *coder)
{
	if (usable_dongle(sim, coder->right_dongle) == 1
		&& usable_dongle(sim, coder->left_dongle) == 1)
		return (1);
	return (0);
}

int	usable_dongle(t_simulation *sim, t_dongle *dongle)
{
	long long	actual_time;

	pthread_mutex_lock(&dongle->dongle_mutex);
	actual_time = get_time_ms();
	if (actual_time - dongle->cooldown_starting_time
		>= sim->config->dongle_cooldown)
		dongle->is_chilled = 1;
	else
		dongle->is_chilled = 0;
	if (dongle->is_connected == 1)
	{
		pthread_mutex_unlock(&dongle->dongle_mutex);
		return (0);
	}
	if (dongle->is_chilled == 0)
	{
		pthread_mutex_unlock(&dongle->dongle_mutex);
		return (0);
	}
	pthread_mutex_unlock(&dongle->dongle_mutex);
	return (1);
}

void	use_dongles(t_coder *coder)
{
	coder->right_dongle->is_connected = 1;
	coder->left_dongle->is_connected = 1;
}


