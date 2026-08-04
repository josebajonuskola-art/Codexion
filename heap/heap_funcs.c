/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 20:41:04 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/29 20:41:33 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	heap_add_fifo(t_simulation *sim, t_request request)
{
	sim->heap->requests[sim->heap->size] = request;
	sim->heap->size++;
}



void    heap_push(t_simulation *sim, t_request request)
{
    //printf("PUSH coder=%d\n", request->coder->n_coder);
	sim->heap->requests[sim->heap->size] = request;
	//printf("PUSH coder=%d\n", request->coder->n_coder);
    sim->heap->size++;
	//printf("PUSH coder=%d\n", request->coder->n_coder);
	printf("ANTES\n");
	print_heap(sim->heap);
    heapify_up(sim, sim->heap);
	printf("DESPUES\n");
	print_heap(sim->heap);
}

t_request   heap_pop(t_simulation *sim)
{
    t_request first_request;
	printf("POP size=%d\n", sim->heap->size);
    first_request = sim->heap->requests[0];
	printf("POP size=%d\n", sim->heap->size);
    sim->heap->requests[0] = sim->heap->requests[sim->heap->size - 1];
	printf("POP size=%d\n", sim->heap->size);
	sim->heap->size--;
	printf("POP size=%d\n", sim->heap->size);
    heapify_down(sim);
	printf("POP size=%d\n", sim->heap->size);
	return (first_request);
}

void    heapify_up(t_simulation *sim, t_heap *heap)
{
    int parent;
    int i;

    i = sim->heap->size - 1;
    while (i > 0)
    {
        parent = (i - 1) / 2;
        if(has_to_heapify(sim, &heap->requests[i], &heap->requests[parent]))
            swapper(&heap->requests[i], &heap->requests[parent]);
        else
            break;
        i = parent;
    }
}

void heapify_down(t_simulation *sim)
{
    int left_son;
    int right_son;
    int biggest;
    int i;

    i = 0;
    while(2 * i + 1 < sim->heap->size)
    {
        left_son = 2 * i + 1;
        right_son = 2 * i + 2;
        biggest = i;
		printf("i=%d left=%d right=%d size=%d\n",
       i, left_son, right_son, sim->heap->size);
        if((left_son < sim->heap->size) && (has_to_heapify(sim, &sim->heap->requests[left_son], &sim->heap->requests[biggest])))
			biggest = left_son;
		if((right_son < sim->heap->size) && (has_to_heapify(sim, &sim->heap->requests[right_son], &sim->heap->requests[biggest])))
			biggest = right_son;
        if (biggest == i)
            break;
		printf("i=%d left=%d right=%d size=%d\n",
       i, left_son, right_son, sim->heap->size);
        swapper(&sim->heap->requests[biggest], &sim->heap->requests[i]);
		printf("i=%d left=%d right=%d size=%d\n",
       i, left_son, right_son, sim->heap->size);
        i = biggest;
    }
}
