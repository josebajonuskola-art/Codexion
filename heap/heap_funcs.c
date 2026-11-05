/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 20:41:04 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/05 22:52:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_request	heap_pop(t_simulation *sim)
{
	t_request	first_request;

	first_request = sim->heap->requests[0];
	sim->heap->requests[0] = sim->heap->requests[sim->heap->size - 1];
	sim->heap->size--;
	heapify_down(sim);
	return (first_request);
}

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

void	heap_push(t_simulation *sim, t_request request)
{
	sim->heap->requests[sim->heap->size] = request;
	sim->heap->size++;
	heapify_up(sim, sim->heap);
}
