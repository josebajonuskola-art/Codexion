/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_verify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:47:13 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/30 13:07:16 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

long long get_smaller_time(t_simulation *sim, t_coder *coder)
{
	long long actual_time;
	long long right_dongles_time;
	long long left_dongles_time;


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

void	request_verify(t_simulation *sim, t_coder *coder)
{
	long long deadline;
	struct timespec deadline_ms;

	pthread_mutex_lock(&sim->heap->heap_mutex);
/* 	while ((has_better_neighbours(sim, coder) != 0)
		|| (usable_dongle(sim, coder->right_dongle) != 1)
		|| (usable_dongle(sim, coder->left_dongle) != 1))
	{
		deadline = get_smaller_time(sim, coder);
		deadline_ms.tv_sec = deadline / 1000;
		deadline_ms.tv_nsec = (deadline % 1000) * 1000000;
		if (deadline > get_time_ms())
			pthread_cond_timedwait(&sim->heap->heap_cond,
				&sim->heap->heap_mutex, &deadline_ms);
		else
			pthread_cond_wait(&sim->heap->heap_cond, &sim->heap->heap_mutex);
	} */
	while (coder->can_process == 0)
	{
		deadline = get_smaller_time(sim, coder);
		deadline_ms.tv_sec = deadline / 1000;
		deadline_ms.tv_nsec = (deadline % 1000) * 1000000;
		if (deadline > get_time_ms())
			pthread_cond_timedwait(&sim->heap->heap_cond,
				&sim->heap->heap_mutex, &deadline_ms);
		else
			pthread_cond_wait(&sim->heap->heap_cond, &sim->heap->heap_mutex);
	}
	pthread_mutex_unlock(&sim->heap->heap_mutex);
}

