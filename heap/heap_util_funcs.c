/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_util_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 12:59:22 by juskola-          #+#    #+#             */
/*   Updated: 2026/08/03 12:59:55 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int is_heap_top(t_simulation *sim, t_coder *coder)
{
    if(sim->heap->requests->coder == coder)
        return (1);
    return (0);
}

int has_to_heapify(t_simulation *sim, t_request *request_top, t_request *request_bottom)
{
	// I don't know if the logic with the arrival numver is okay
    if(usable_dongle(sim, request_top))
	if(sim->config->scheduler == FIFO && request_top->arrival_number < request_bottom->arrival_number)
		return (1);
	//The logic of the 'EDF' has to be checked again
	else if(sim->config->scheduler == EDF && request_top->time_remaining > request_bottom->time_remaining)
		return (1);
	else
		return (0);
}

void	swapper(t_request *request_top, t_request *request_bottom)
{
	t_request temporal;

	temporal = *request_top;
	*request_top = *request_bottom;
	*request_bottom = temporal;
}

void    print_heap(t_heap *heap)
{
    int i;

    i = 0;
    printf("\n===== HEAP =====\n");
    printf("size = %d\n", heap->size);
    while (i < heap->size)
    {
        printf("[%d] coder=%d arrival=%d deadline=%lld\n",
            i,
            heap->requests[i].coder->n_coder,
            heap->requests[i].arrival_number,
            heap->requests[i].time_remaining);
        i++;
    }
    printf("================\n");
}
