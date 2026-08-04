/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 13:42:14 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/17 17:49:56 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../codexion.h"

// This function frees all memory allocated for the simulation.
//
// The 'simulation' pointer references the simulation structure,
// allowing all dynamically allocated resources associated with it
// to be released.
void	sim_garbage_collector(t_simulation *simulation)
{
	free(simulation->coders);
	free(simulation->dongles);
	free(simulation->monitor);
	free(simulation);
}
