/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_util_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 12:59:22 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 17:00:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function determines whether two request elements in the heap should be
// swapped during heapification based on the configured scheduling algorithm
// (FIFO or EDF).
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'request_top' parameter is a pointer to the upper request in the heap
// comparison. The 'request_bottom' parameter is a pointer to the lower
// request in the heap comparison.
int	has_to_heapify(t_simulation *sim,
	t_request *request_top, t_request *request_bottom)
{
	if (sim->config->scheduler == FIFO
		&& request_top->arrival_number < request_bottom->arrival_number)
		return (1);
	else if (sim->config->scheduler
		== EDF && request_top->time_remaining < request_bottom->time_remaining)
		return (1);
	else
		return (0);
}

// This function checks whether the request belonging to a given coder
// is currently located at the top (root) of the request heap.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder structure to check.
int	is_heap_top(t_simulation *sim, t_coder *coder)
{
	if (sim->heap->requests->coder == coder)
		return (1);
	return (0);
}

// This function swaps the contents of two t_request structures in memory.
//
// The 'request_top' parameter is a pointer to the first request structure.
// The 'request_bottom' parameter is a pointer to the second request structure.
void	swapper(t_request *request_top, t_request *request_bottom)
{
	t_request	temporal;

	temporal = *request_top;
	*request_top = *request_bottom;
	*request_bottom = temporal;
}
