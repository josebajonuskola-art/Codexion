/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_research.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:01:22 by juskola-          #+#    #+#             */
/*   Updated: 2026/10/28 10:01:38 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_coder	*find_right_neighbour(t_simulation *sim, t_coder *coder)
{
	t_coder *coder_right;

	if (coder->n_coder == 1)
		coder_right = &sim->coders[sim->config->number_of_coders - 1];
	else
		coder_right = &sim->coders[coder->n_coder - 2];

	return (coder_right);
}

t_coder	*find_left_neighbour(t_simulation *sim, t_coder *coder)
{
	t_coder *coder_left;

	if (coder->n_coder == sim->config->number_of_coders)
		coder_left = &sim->coders[0];
	else
		coder_left = &sim->coders[coder->n_coder];

	return (coder_left);
}

int		has_better_neighbours(t_simulation *sim, t_coder *coder)
{
	t_coder *coder_right;
	t_coder *coder_left;
	t_request *coder_request;
	t_request *right_coder_request;
	t_request *left_coder_request;

	coder_request = find_request(sim, coder);
	if (!coder_request)
		return (0);
	coder_right = find_right_neighbour(sim, coder);
	right_coder_request = find_request(sim, coder_right);
	if (!right_coder_request)
		return (0);
	coder_left = find_left_neighbour(sim, coder);
	left_coder_request = find_request(sim, coder_left);
	if (!left_coder_request)
		return (0);

	if (has_to_heapify(sim, right_coder_request, coder_request)
		|| has_to_heapify(sim, left_coder_request, coder_request))
		return (1);
	return (0);
}

t_request	*find_request(t_simulation *sim, t_coder *coder)
{
	int	i;

	i = 0;
	while (i < sim->heap->size)
	{
		if (coder->n_coder == sim->heap->requests[i].coder->n_coder)
			return (&sim->heap->requests[i]);
		i++;
	}
	return (NULL);
}
