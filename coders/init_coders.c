/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 16:39:40 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 17:35:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function sets default baseline values for a coder at the given index,
// initializing its ID, compilation count, timestamp, execution flags, right
// dongle pointer, and simulation reference.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'i' parameter is the integer index of the coder being initialized.
void	coder_pattern_factory(t_simulation *sim, int i)
{
	sim->coders[i].n_coder = i + 1;
	sim->coders[i].n_compiles_done = 0;
	sim->coders[i].last_compile = get_time_ms();
	sim->coders[i].actual_step = 0;
	sim->coders[i].can_process = 0;
	sim->coders[i].right_dongle = &sim->dongles[i];
	sim->coders[i].sim = sim;
}

// This function initializes all coders in the simulation by applying the baseline
// configuration pattern, assigning circular left dongles, and initializing each
// coder's mutex.
//
// The 'sim' parameter is a pointer to the main simulation structure whose coders
// are initialized.
int	init_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		coder_pattern_factory(sim, i);
		if (sim->config->number_of_coders == 1)
			sim->coders[i].left_dongle = &sim->dongles[i + 1];
		else if (i == sim->config->number_of_coders - 1)
			sim->coders[i].left_dongle = &sim->dongles[0];
		else
			sim->coders[i].left_dongle = &sim->dongles[i + 1];
		if (pthread_mutex_init(&sim->coders[i].coder_mutex, NULL) != 0)
		{
			mtx_destroyer(0, i, sim);
			return (garbage_collector(sim), 1);
		}
		i++;
	}
	return (0);
}
