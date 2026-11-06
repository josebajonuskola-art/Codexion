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
void	garbage_collector(t_simulation *simulation)
{
	if (simulation->avl_coders)
		free(simulation->avl_coders);
	if (simulation->not_avl_coders)
		free(simulation->not_avl_coders);
	if (simulation->coders)
		free(simulation->coders);
	if (simulation->dongles)
		free(simulation->dongles);
	if (simulation->monitor)
		free(simulation->monitor);
	if (simulation->heap)
	{
		if (simulation->heap->requests)
			free(simulation->heap->requests);
		free(simulation->heap);
	}
	if (simulation->heap_sorter)
		free(simulation->heap_sorter);
	if (simulation)
		free(simulation);
}
