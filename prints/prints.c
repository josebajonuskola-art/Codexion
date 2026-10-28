/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:40:04 by juskola-          #+#    #+#             */
/*   Updated: 2026/10/21 11:40:31 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void print_take_dongles(t_simulation *sim, t_coder *coder)
{
	long long	actual_time;

	actual_time = get_time_ms() - sim->start_time;
	printf("%lld %d has taken a dongle\n",
		actual_time, coder->n_coder);
	printf("%lld %d has taken a dongle\n",
		actual_time, coder->n_coder);
}

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
