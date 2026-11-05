/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 16:41:04 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/05 16:41:21 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function initializes all dongles in the simulation.
//
// The 'sim' pointer references the simulation structure whose
// dongle fields are initialized.
int	init_dongles(t_simulation *sim)
{
	int	i;

	i = 0;
	printf("Before init dongles\n");
	while (i < sim->config->number_of_coders)
	{
		printf("Before2 init dongles\n");
		sim->dongles[i].n_dongle = i;
		sim->dongles[i].is_connected = 0;
		sim->dongles[i].is_chilled = 0;
		sim->dongles[i].cooldown_starting_time = 0;
		sim->dongles[i].user = NULL;
		if (pthread_mutex_init(&sim->dongles[i].dongle_mutex, NULL) != 0)
		{
			mtx_destroyer(1, i, sim);
			return (1);
		}
		i++;
	}
	printf("After init dongles\n");
	return (0);
}
