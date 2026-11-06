/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:32:18 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 17:40:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function serves as the entry point routine for each coder thread.
// It casts the void pointer parameter to a t_coder pointer and launches
// the main execution loop for that coder via run_coders.
//
// The 'value' parameter is a void pointer referencing the t_coder structure.
void	*init_coders_threads(void *value)
{
	t_coder	*coder;

	coder = (t_coder *)value;
	run_coders(coder->sim, coder);
	return (NULL);
}

// This function executes the main lifecycle loop of a coder. It registers the
// initial compilation request in the heap and repeatedly verifies request
// authorization and executes the compilation/debug/refactor cycle until the
// simulation reaches completion.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the individual coder structure.
void	run_coders(t_simulation *sim, t_coder *coder)
{
	coder_request(sim, coder);
	while (sim_is_finished(sim) == 0)
	{
		if (sim_is_finished(sim) == 1)
			break ;
		request_verify(sim, coder);
		if (sim_is_finished(sim) == 1)
			break ;
		if (coder_process(coder->sim, coder) == 1)
			break ;
	}
}
