/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:40:04 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/06 16:35:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function prints the elements currently present in the request heap
// for debugging purposes, showing the size, coder ID, arrival number,
// and remaining time for each request.
//
// The 'heap' parameter is a pointer to the heap structure to be displayed.
void	print_heap(t_heap *heap)
{
	int	i;

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

// This function handles the thread-safe printing of a coder's current status
// (compiling, debugging, or refactoring) as long as the simulation has not
// finished.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder changing state.
// The 'status' parameter is an integer representing the current state
// (0 for compile, 1 for debug, and 2 for refactor).
void	print_process(t_simulation *sim, t_coder *coder, int status)
{
	pthread_mutex_lock(&sim->print_mutex);
	if (sim_is_finished(sim) == 0)
	{
		if (status == 0)
			print_start_to_compile(sim, coder);
		else if (status == 1)
			printf("%lld %d is debugging\n",
				get_time_ms() - sim->start_time, coder->n_coder);
		else
			printf("%lld %d is refactoring\n",
				get_time_ms() - sim->start_time, coder->n_coder);
	}
	pthread_mutex_unlock(&sim->print_mutex);
}

// This function prints the three sequence lines indicating that a coder
// has taken two dongles and started compiling, using a unified timestamp
//  calculation.
//
// The 'sim' parameter is a pointer to the main simulation structure.
// The 'coder' parameter is a pointer to the coder starting to compile.
void	print_start_to_compile(t_simulation *sim, t_coder *coder)
{
	long long	actual_time;

	actual_time = get_time_ms() - sim->start_time;
	printf("%lld %d has taken a dongle\n",
		actual_time, coder->n_coder);
	printf("%lld %d has taken a dongle\n",
		actual_time, coder->n_coder);
	printf("%lld %d is compiling\n",
		actual_time, coder->n_coder);
}
