/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:40:52 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/29 18:41:12 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	init_heap(t_simulation *sim)
{
	sim->heap = malloc(sizeof(t_heap));
	if (!sim->heap)
		return (1);
	sim->heap->requests
		= malloc((sizeof(t_request)) * sim->config->number_of_coders);
	if (!sim->heap->requests)
		return (1);
	sim->heap->size = 0;
	sim->heap->capacity = sim->config->number_of_coders;
	sim->arrival_counter = 0;
	if (pthread_mutex_init(&sim->heap->heap_mutex, NULL) != 0)
		mtx_destroyer(2, 2, sim);
	if (pthread_cond_init(&sim->heap->heap_cond, NULL) != 0)
		pthread_cond_destroy(&sim->heap->heap_cond);
	return (0);
}
