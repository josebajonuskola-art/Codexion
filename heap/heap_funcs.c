/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 20:41:04 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 17:25:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function removes and returns the highest priority request from the top
// of the heap (index 0), replaces it with the last element, decrements the
// heap size, and restores the heap property using heapify_down.
//
// The 'sim' parameter is a pointer to the main simulation structure.
t_request	heap_pop(t_simulation *sim)
{
	t_request	first_request;

	first_request = sim->heap->requests[0];
	sim->heap->requests[0] = sim->heap->requests[sim->heap->size - 1];
	sim->heap->size--;
	heapify_down(sim);
	return (first_request);
}

// This function restores the min-heap property downwards starting from the
// root (index 0). It repeatedly compares the parent node with its left and
// right children and swaps with the smallest child if necessary until
// the heap order is restored.
//
// The 'sim' parameter is a pointer to the main simulation structure.
void	heapify_down(t_simulation *sim)
{
	int	left_son;
	int	right_son;
	int	biggest;
	int	i;

	i = 0;
	while (2 * i + 1 < sim->heap->size)
	{
		left_son = 2 * i + 1;
		right_son = 2 * i + 2;
		biggest = i;
		if ((left_son < sim->heap->size)
			&& (has_to_heapify(sim, &sim->heap->requests[left_son],
					&sim->heap->requests[biggest])))
			biggest = left_son;
		if ((right_son < sim->heap->size)
			&& (has_to_heapify(sim, &sim->heap->requests[right_son],
					&sim->heap->requests[biggest])))
			biggest = right_son;
		if (biggest == i)
			break ;
		swapper(&sim->heap->requests[biggest], &sim->heap->requests[i]);
		i = biggest;
	}
}

// This function restores the min-heap property upwards starting
// from the last element in the heap. It repeatedly compares the element
// with its parent and swaps them if required by the scheduling criteria
// until the proper position is found.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'heap' parameter is a pointer to the heap structure containing
// the requests.
void	heapify_up(t_simulation *sim, t_heap *heap)
{
	int	parent;
	int	i;

	i = sim->heap->size - 1;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (has_to_heapify(sim, &heap->requests[i], &heap->requests[parent]))
			swapper(&heap->requests[i], &heap->requests[parent]);
		else
			break ;
		i = parent;
	}
}

// This function inserts a new request into the heap by appending it to the end
// of the array, incrementing the heap size, and re-balancing the heap upwards
// using heapify_up.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'request' parameter is the request structure to be added to the heap.
void	heap_push(t_simulation *sim, t_request request)
{
	sim->heap->requests[sim->heap->size] = request;
	sim->heap->size++;
	heapify_up(sim, sim->heap);
}
